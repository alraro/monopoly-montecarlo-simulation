#include "Game.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    std::cout << "Random seed: " << initRandom() << std::endl;

    Game game;

    game.setDefaultBoard()
        .addPlayer("Alice")
        .addPlayer("Bob")
        .runSimulation(1000000);

    return 0;
}