#include "Simulation.hpp"
#include "Game.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <queue>

Simulation::Simulation(const SimulationConfig &config) : _config(config) {}

namespace {
    void runSingleGameFromQueue(std::queue<Game> &gameQueue, size_t turnLimit, std::mutex &gameMutex) {
        while (true) {
                std::unique_lock<std::mutex> lock(gameMutex);
                if (gameQueue.empty()) {
                    return;
                }
                Game game = std::move(gameQueue.front());
                gameQueue.pop();
                lock.unlock();

                game.play(turnLimit);
        }
    }

    void runSingleGame(const SimulationConfig &rules, size_t turnLimit) {
        Game game(rules);
        game.play(turnLimit);
    }
}

void Simulation::runParallelMontecarloSimulation(size_t games, size_t turnLimit, size_t numThreads) {

    std::vector<std::thread> threads;
    std::mutex gameMutex;

    std::queue<Game> gameQueue;

    for (size_t i = 0; i < games; ++i) {
        gameQueue.emplace(_config);
    }

    threads.reserve(numThreads);
    for (size_t i = 0; i < numThreads; ++i) {
        std::thread gameThread(runSingleGameFromQueue, std::ref(gameQueue), turnLimit, std::ref(gameMutex));
        threads.push_back(std::move(gameThread));
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