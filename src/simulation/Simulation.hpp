#pragma once

#include "SimulationConfig.hpp"
#include <thread>
#include "GenericViewComponents.hpp"
#include "interface/GenericViewComponents.hpp"

class Simulation {
    private:
        SimulationConfig  _config;
        IProgressView    &_progressView;
    public:
        Simulation(const SimulationConfig &config, IProgressView &progressView): _config(config), _progressView(progressView) {};
    
        void runParallelMontecarloSimulation(size_t games, size_t turnLimit, size_t numThreads = std::thread::hardware_concurrency());
        void runSequentialMontecarloSimulation(size_t games, size_t turnLimit);
        void run();
};
