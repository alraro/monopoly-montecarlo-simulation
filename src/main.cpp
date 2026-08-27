#include "Game.hpp"
#include "utils.hpp"
#include <iostream>
#include "BoardFactory.hpp"

int main() {
    constexpr unsigned int TURNS = 10000;
    constexpr unsigned int SEED = 123456;
    std::cout << "Random seed: " << initRandom(SEED) << std::endl;

    Game game1 = Game().setDefaultBoard().addPlayer("Alice").addPlayer("Bob");
    game1.runSimulation(TURNS);
    game1.printStatistics();
    game1.exportStatisticsToCSV("players_statistics.csv", "squares_statistics.csv");
    return 0;
}