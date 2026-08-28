#ifndef SIMULATION_HPP
# define SIMULATION_HPP
# include "SimulationRules.hpp"

class Simulation {
    private:
        SimulationRules _rules;
    public:
        Simulation(const std::vector<SquareInfo> &squares, const std::vector<PlayerInfo> &players);
        void runMontecarloSimulation(unsigned int games);
};

#endif
