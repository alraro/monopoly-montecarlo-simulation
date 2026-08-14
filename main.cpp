#include "Game.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    constexpr unsigned int TURNS = 10000;
    constexpr unsigned int SEED = 12345;
    std::cout << "Random seed: " << initRandom(SEED) << std::endl;

    Game game;

    game.setDefaultBoard()
        .addPlayer("Alice")
        .addPlayer("Bob")
        .runSimulation(TURNS);

    return 0;
}