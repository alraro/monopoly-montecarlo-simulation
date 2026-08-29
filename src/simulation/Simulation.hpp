#ifndef SIMULATION_HPP
# define SIMULATION_HPP
# include "SimulationRules.hpp"
# include <thread>

class Simulation {
    private:
        SimulationRules _rules;
    public:
        Simulation(const std::vector<SquareInfo> &squares, const std::vector<PlayerInfo> &players);
        void runParallelMontecarloSimulation(size_t games, size_t numThreads = std::thread::hardware_concurrency());
        void runSequentialMontecarloSimulation(size_t games);
};

#endif
