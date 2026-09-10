#pragma once

#include "SimulationConfig.hpp"
#include "GenericViewComponents.hpp"
#include "interface/GenericViewComponents.hpp"
#include "Game.hpp"

class Simulation {
    private:
        SimulationConfig        _config;
        IProgressView          &_progressView;
        std::atomic<uint64_t>   _completedGames = 0;
        bool                    _shouldStop = false;

        void _runSingleGameFromQueue(std::vector<Game> &gameList, size_t turnLimit, std::atomic<size_t> &nextGameIndex);
        void _runSingleGame(const SimulationConfig &rules, size_t turnLimit);
        
    public:
        Simulation(const SimulationConfig &config, IProgressView &progressView): _config(config), _progressView(progressView) {};
    
        void runParallelMontecarloSimulation();
        void runSequentialMontecarloSimulation();
        void run();
        void stop() { _shouldStop = true; };
};
