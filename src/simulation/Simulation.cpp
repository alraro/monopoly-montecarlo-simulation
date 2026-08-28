#include "Simulation.hpp"
#include "Game.hpp"

Simulation::Simulation(const std::vector<SquareInfo> &squares, const std::vector<PlayerInfo> &players): _rules({squares, players}) {}

void Simulation::runMontecarloSimulation(unsigned int games) {
    for (unsigned int i = 0; i < games; ++i) {
        Game game(_rules);
        game.play(1000); //TODO: Make the number of turns configurable
    }
}