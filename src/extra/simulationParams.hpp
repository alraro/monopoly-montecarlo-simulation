#ifndef SIMULATIONPARAMS_HPP
# define SIMULATIONPARAMS_HPP
# include "Logger.hpp"
# include <cstdint>

constexpr uint64_t DEFAULT_TURNS = 1000;
constexpr uint64_t DEFAULT_SEED = 123456;
constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::Progress;

struct SimulationParams {
    uint64_t turns = DEFAULT_TURNS;
    uint64_t seed = DEFAULT_SEED;
    LogLevel logLevel = DEFAULT_LOG_LEVEL;
    std::string playersStatisticsFilename = "";
    std::string squaresStatisticsFilename = "";
    bool runInParallel = false;
};

#endif