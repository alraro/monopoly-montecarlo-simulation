#pragma once
#include "Logger.hpp"
#include <cstdint>
#include <vector>
#include "PlayerInfo.hpp"
#include "SquareInfo.hpp"

constexpr uint64_t DEFAULT_TURNS = 1000;
constexpr uint64_t DEFAULT_SEED = 123456;
constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::Progress;

struct SimulationConfig {
    uint64_t turns = DEFAULT_TURNS;
    uint64_t seed = DEFAULT_SEED;
    LogLevel logLevel = DEFAULT_LOG_LEVEL;
    std::vector<PlayerInfo> players;
    std::vector<SquareInfo> squares;
    std::string playersStatisticsFilename = "";
    std::string squaresStatisticsFilename = "";
    bool runInParallel = false;

    void addPlayer(PlayerId id, const std::string &name) {
        players.emplace_back(id, name);
    }

};
