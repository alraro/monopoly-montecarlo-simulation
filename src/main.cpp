#include "Game.hpp"
#include "utils.hpp"
#include <iostream>
#include "BoardFactory.hpp"
#include "Logger.hpp"

int main() {
    Logger::setLogLevel(LogLevel::None);
    constexpr unsigned int TURNS = 10000000;
    constexpr unsigned int SEED = 123456;\
    Logger::info("Random seed: ", initRandom(SEED));

    Game game1 = Game().setDefaultBoard().addPlayer("Alice").addPlayer("Bob");
    game1.runSimulation(TURNS);
    game1.printStatistics();
    game1.exportStatisticsToCSV("players_statistics.csv", "squares_statistics.csv");
    return 0;
}