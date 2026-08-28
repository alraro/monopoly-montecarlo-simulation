#ifndef SIMULATIONPARAMS_HPP
# define SIMULATIONPARAMS_HPP
# include "Logger.hpp"

constexpr unsigned int DEFAULT_TURNS = 100000;
constexpr unsigned int DEFAULT_SEED = 123456;
constexpr LogLevel DEFAULT_LOG_LEVEL = LogLevel::Info;

struct SimulationParams {
    unsigned int turns = DEFAULT_TURNS;
    unsigned int seed = DEFAULT_SEED;
    LogLevel logLevel = DEFAULT_LOG_LEVEL;
    std::string playersStatisticsFilename = "";
    std::string squaresStatisticsFilename = "";
};

#endif