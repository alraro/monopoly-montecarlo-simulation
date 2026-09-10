#include "Simulation.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include <thread>

namespace {
    void runSingleGame(const SimulationConfig &config, GameId gameId, bool &shouldStop) {
        Game game(config, gameId, shouldStop);
        game.play();
    }

    void runGamesWorker(const SimulationConfig &config, size_t threadIndex, std::atomic<uint64_t> &completedGames, bool &shouldStop) {
        uint64_t baseGamesPerThread = config.gameCount / config.numThreads;
        uint64_t remainder = config.gameCount % config.numThreads;

        uint64_t gamesForThisThread = baseGamesPerThread + (threadIndex < remainder ? 1 : 0);
        uint64_t startIndex = (baseGamesPerThread * threadIndex) + std::min(threadIndex, remainder);
        uint64_t endIndex = startIndex + gamesForThisThread;

        for (uint64_t i = startIndex; i < endIndex; ++i) {
            runSingleGame(config, i, shouldStop);
            completedGames.fetch_add(1, std::memory_order_relaxed);
        }
    }
}

void Simulation::runParallelMontecarloSimulation() {

    std::vector<std::thread> threads;

    threads.reserve(_config.numThreads);
    for (size_t i = 0; i < _config.numThreads; ++i) {
        threads.emplace_back(runGamesWorker, std::ref(_config), i, std::ref(_completedGames), std::ref(_shouldStop));
    }
    
    uint64_t lastCompletedCount = 0;
    while (lastCompletedCount < _config.gameCount) {
        if (_shouldStop) {
            Logger::info("Simulation stopped by user.");
            break;
        }
        lastCompletedCount = _completedGames.load(std::memory_order_relaxed);
        this->_progressView.updateProgress(lastCompletedCount, _config.gameCount);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    int count = 0;
    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
            ++count;
            Logger::info("Completed thread ", count, " of ", _config.numThreads);
        }
    }
}

void Simulation::runSequentialMontecarloSimulation() {
    for (uint64_t i = 0; i < _config.gameCount; ++i) {
        if (_shouldStop) {
            Logger::info("Simulation stopped by user.");
            return ;
        }
        runSingleGame(_config, i, _shouldStop);
        Logger::info("Completed game ", (i + 1), " of ", _config.gameCount);
        _completedGames.fetch_add(1, std::memory_order_relaxed);
        this->_progressView.updateProgress(i + 1, _config.gameCount);
    }
}

void Simulation::run() {
    if (_config.runInParallel) {
        Logger::setLogLevel(_config.logLevel = LogLevel::None);
        runParallelMontecarloSimulation();
    } else {
        Logger::setLogLevel(_config.logLevel);
        runSequentialMontecarloSimulation();
    }
}
