#include "Simulation.hpp"
#include "Game.hpp"
#include <thread>
#include <iostream>

Simulation::Simulation(const SimulationConfig &config) : _config(config) {}

namespace {
    void runSingleGameFromQueue(std::vector<Game> &gameList, size_t turnLimit, std::atomic<size_t> &nextGameIndex) {
        while (true) {
                size_t index = nextGameIndex.fetch_add(1, std::memory_order_relaxed);
                if (index >= gameList.size()) {
                    return ;
                }
                gameList[index].play(turnLimit);
        }
    }

    void runSingleGame(const SimulationConfig &rules, size_t turnLimit) {
        static GameId gameCounter = 0;
        Game game(rules, gameCounter++);
        game.play(turnLimit);
    }
}

void Simulation::runParallelMontecarloSimulation(size_t games, size_t turnLimit, size_t numThreads) {

    std::vector<std::thread> threads;
    std::atomic<size_t> nextGameIndex(0);

    std::vector<Game> gamesList;
    gamesList.reserve(games);

    for (size_t i = 0; i < games; ++i) {
        gamesList.emplace_back(_config, static_cast<GameId>(i));
    }

    threads.reserve(numThreads);
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(runSingleGameFromQueue, std::ref(gamesList), turnLimit, std::ref(nextGameIndex));
    }
    
    int count = 0;
    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
            ++count;
            std::cout << "Completed thread " << count << " of " << numThreads << std::endl;
        }
    }
}

void Simulation::runSequentialMontecarloSimulation(size_t games, size_t turnLimit) {
    for (size_t i = 0; i < games; ++i) {
        runSingleGame(_config, turnLimit);
        std::cout << "Completed game " << (i + 1) << " of " << games << std::endl;
    }
}

void Simulation::run() {

    if (_config.runInParallel) {
        _config.logLevel = LogLevel::None;
        Logger::setLogLevel(_config.logLevel);
        runParallelMontecarloSimulation(_config.gameCount, _config.turnLimit, _config.numThreads);
    } else {
        runSequentialMontecarloSimulation(_config.gameCount, _config.turnLimit);
    }
}