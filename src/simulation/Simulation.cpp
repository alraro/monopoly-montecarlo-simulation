#include "Simulation.hpp"
#include "Game.hpp"
#include "Logger.hpp"
#include <thread>
#include <iostream>

namespace {
    void runSingleGame(const SimulationConfig &config, GameId gameId) {
        Game game(config, gameId);
        game.play();
    }

    void runGamesWorker(const SimulationConfig &config, size_t threadIndex, std::atomic<uint64_t> &completedGames) {
        uint64_t baseGamesPerThread = config.gameCount / config.numThreads;
        uint64_t remainder = config.gameCount % config.numThreads;

        uint64_t gamesForThisThread = baseGamesPerThread + (threadIndex < remainder ? 1 : 0);
        uint64_t startIndex = (baseGamesPerThread * threadIndex) + std::min(threadIndex, remainder);
        uint64_t endIndex = startIndex + gamesForThisThread;

        for (uint64_t i = startIndex; i < endIndex; ++i) {
            runSingleGame(config, i);
            completedGames.fetch_add(1, std::memory_order_relaxed);
        }
    }
}

void Simulation::runParallelMontecarloSimulation() {

    std::vector<std::thread> threads;

    threads.reserve(_config.numThreads);
    for (size_t i = 0; i < _config.numThreads; ++i) {
        threads.emplace_back(runGamesWorker, std::ref(_config), i, std::ref(_completedGames));
    }
    
    uint64_t lastCompletedCount = 0;
    while (lastCompletedCount < _config.gameCount) {
        lastCompletedCount = _completedGames.load(std::memory_order_relaxed);
        this->_progressView.updateProgress(lastCompletedCount, _config.gameCount);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    int count = 0;
    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
            ++count;
            std::cout << "Completed thread " << count << " of " << _config.numThreads << std::endl;
        }
    }
}


void Simulation::runSequentialMontecarloSimulation() {
    for (uint64_t i = 0; i < _config.gameCount; ++i) {
        runSingleGame(_config, _config.turnLimit);
        std::cout << "Completed game " << (i + 1) << " of " << _config.gameCount << std::endl;
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