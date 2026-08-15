#include "Game.hpp"
#include "utils.hpp"
#include <iostream>
#include "BoardFactory.hpp"

int main() {
    constexpr unsigned int TURNS = 10000;
    constexpr unsigned int SEED = 12345;
    std::cout << "Random seed: " << initRandom(SEED) << std::endl;

    Game game1 = Game().setDefaultBoard().addPlayer("Alice").addPlayer("Bob");

    game1.runSimulation(TURNS);
    return 0;
}