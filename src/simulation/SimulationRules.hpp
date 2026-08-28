#ifndef SIMULATIONRULES_HPP
# define SIMULATIONRULES_HPP
# include <vector>
# include "SquareInfo.hpp"
# include "PlayerInfo.hpp"

struct SimulationRules {
    std::vector<SquareInfo> squares;
    std::vector<PlayerInfo> players;
};

#endif