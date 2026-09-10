#include "Simulation.hpp"
#include "Game.hpp"
#include <thread>
#include <iostream>

namespace {
    void runSingleGameFromQueue(std::vector<Game> &gameList, size_t turnLimit, std::atomic<size_t> &nextGameIndex, std::atomic<uint64_t> &completedGames) {
        while (true) {
                size_t index = nextGameIndex.fetch_add(1, std::memory_order_relaxed);
                if (index >= gameList.size()) {
                    return ;
                }
                gameList[index].play(turnLimit);
                completedGames.fetch_add(1, std::memory_order_relaxed);
        }
    }

    void runSingleGame(const SimulationConfig &rules, size_t turnLimit, std::atomic<uint64_t> &completedGames) {
        static GameId gameCounter = 0;
        Game game(rules, gameCounter++);
        game.play(turnLimit);
        completedGames.fetch_add(1, std::memory_order_relaxed);
    }
}

void Simulation::runParallelMontecarloSimulation() {

    std::vector<std::thread> threads;
    std::atomic<size_t> nextGameIndex(0);

    std::vector<Game> gamesList;
    gamesList.reserve(_config.gameCount);

    for (size_t i = 0; i < _config.gameCount; ++i) {
        gamesList.emplace_back(_config, static_cast<GameId>(i));
    }

    threads.reserve(_config.numThreads);
    for (size_t i = 0; i < _config.numThreads; ++i) {
        threads.emplace_back(runSingleGameFromQueue, std::ref(gamesList), _config.turnLimit, std::ref(nextGameIndex), std::ref(_completedGames));
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
        runSingleGame(_config, _config.turnLimit, _completedGames);
        std::cout << "Completed game " << (i + 1) << " of " << _config.gameCount << std::endl;
        _completedGames.fetch_add(1, std::memory_order_relaxed);
        this->_progressView.updateProgress(i + 1, _config.gameCount);
    }
}

void Simulation::run() {

    if (_config.runInParallel) {
        _config.logLevel = LogLevel::None;
        Logger::setLogLevel(_config.logLevel);
        runParallelMontecarloSimulation();
    } else {
        runSequentialMontecarloSimulation();
    }
}