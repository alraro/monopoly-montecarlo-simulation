#pragma once

#include <monopoly/simulation/SimulationConfig.hpp>
#include <monopoly/interface/GenericViewComponents.hpp>
#include <atomic>

namespace monopoly {

class Simulation {
    private:
        SimulationConfig        _config;
        IProgressView          &_progressView;
        std::atomic<uint64_t>   _completedGames = 0;
        std::atomic<bool>       _shouldStop;

        public:
        Simulation(const SimulationConfig &config, IProgressView &progressView): _config(config), _progressView(progressView), _shouldStop(false) {};
        
        void runParallelMontecarloSimulation();
        void runSequentialMontecarloSimulation();
        void run();
        void stop() { _shouldStop.store(true, std::memory_order_relaxed); };
        bool isStopped() { return _shouldStop.load(std::memory_order_relaxed); };
};

}
