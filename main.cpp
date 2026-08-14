#include "Game.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    std::cout << "Random seed: " << initRandom(12345) << std::endl;

    Game game;

    game.setDefaultBoard()
        .addPlayer("Alice")
        .addPlayer("Bob")
        .runSimulation(10000);

    return 0;
}