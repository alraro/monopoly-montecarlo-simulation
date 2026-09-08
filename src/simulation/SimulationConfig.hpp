#pragma once
#include "Logger.hpp"
#include <cstdint>
#include "PlayerInfo.hpp"
#include "SquareInfo.hpp"
#include <vector>
#include <thread>

constexpr uint64_t DEFAULT_TURNS = 1000;
constexpr uint64_t DEFAULT_SEED = 123456;
constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::Progress;
constexpr uint64_t DEFULT_GAME_COUNT = 100;

struct SimulationConfig {
    uint64_t turnLimit = DEFAULT_TURNS;
    uint64_t seed = DEFAULT_SEED;
    uint64_t gameCount = DEFULT_GAME_COUNT;
    unsigned int numThreads = std::thread::hardware_concurrency();

    LogLevel logLevel = DEFAULT_LOG_LEVEL;

    std::vector<PlayerInfo> players;
    std::vector<SquareInfo> squares;

    std::string baseDir = ".";
    std::string simulationName = "unnamed_simulation";
    bool exportStatistics = true;

    bool runInParallel = false;

    void addPlayer(PlayerId id, const std::string &name) {
        players.emplace_back(id, name);
    }

    void addSquare(SquareInfo square) {
        squares.push_back(square);
    }

    bool isValid() const {
        if (players.empty()) {
            Logger::error("No players provided in the simulation rules.");
            return false;
        }
        if (squares.empty()) {
            Logger::error("No squares provided in the simulation rules.");
            return false;
        }
        return true;
    }

};
