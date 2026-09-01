#pragma once

#include "SimulationConfig.hpp"
#include <thread>

class Simulation {
    private:
        SimulationConfig _config;
    public:
        Simulation(const SimulationConfig &config);
        void runParallelMontecarloSimulation(size_t games, size_t turnLimit, size_t numThreads = std::thread::hardware_concurrency());
        void runSequentialMontecarloSimulation(size_t games, size_t turnLimit);
        void run();
};
