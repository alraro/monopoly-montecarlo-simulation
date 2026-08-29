#include "Simulation.hpp"
#include "Game.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <queue>

Simulation::Simulation(const std::vector<SquareInfo> &squares, const std::vector<PlayerInfo> &players): _rules({squares, players}) {}

namespace {
    void runSingleGameFromQueue(std::queue<Game> &gameQueue,  std::mutex &gameMutex) {
        while (true) {
                std::unique_lock<std::mutex> lock(gameMutex);
                if (gameQueue.empty()) {
                    return;
                }
                Game game = std::move(gameQueue.front());
                gameQueue.pop();
                lock.unlock();

                game.play(1000000);
        }
    }
}

void Simulation::runParallelMontecarloSimulation(size_t games, size_t numThreads) {

    std::vector<std::thread> threads;
    std::mutex gameMutex;

    std::queue<Game> gameQueue;

    for (size_t i = 0; i < games; ++i) {
        gameQueue.emplace(_rules);
    }

    threads.reserve(numThreads);
    for (size_t i = 0; i < numThreads; ++i) {
        std::thread gameThread(runSingleGameFromQueue, std::ref(gameQueue), std::ref(gameMutex));
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

void runSingleGame(const SimulationRules &rules) {
    Game game(rules);
    game.play(1000000);
}

void Simulation::runSequentialMontecarloSimulation(size_t games) {
    for (size_t i = 0; i < games; ++i) {
        runSingleGame(_rules);
        std::cout << "Completed game " << (i + 1) << " of " << games << std::endl;
    }
}