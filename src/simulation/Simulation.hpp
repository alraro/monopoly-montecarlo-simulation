#pragma once

#include "SimulationConfig.hpp"
#include "GenericViewComponents.hpp"
#include "interface/GenericViewComponents.hpp"

class Simulation {
    private:
        SimulationConfig  _config;
        IProgressView    &_progressView;
    public:
        Simulation(const SimulationConfig &config, IProgressView &progressView): _config(config), _progressView(progressView) {};
    
        void runParallelMontecarloSimulation();
        void runSequentialMontecarloSimulation();
        void run();
};
