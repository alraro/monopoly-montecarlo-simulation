#include "Game.hpp"
#include "utils.hpp"
#include <iostream>
#include "BoardFactory.hpp"

int main() {
    constexpr unsigned int TURNS = 10000;
    constexpr unsigned int SEED = 12345;
    std::cout << "Random seed: " << initRandom(SEED) << std::endl;

    Board defaultBoard = BoardFactory::createDefaultBoard();
    auto sharedBoard = std::make_shared<const Board>(defaultBoard);

    Game game1 = Game().setBoard(sharedBoard).addPlayer("Alice").addPlayer("Bob");
    Game game2 = Game(game1).addPlayer("Charlie");
    Game game3 = Game(game1).addPlayer("David").addPlayer("Eve");

    std::cout << "Running simulation for game1 with " << TURNS << " turns." << std::endl;
    game1.runSimulation(TURNS);
    std::cout << "Running simulation for game2 with " << TURNS << " turns." << std::endl;
    game2.runSimulation(TURNS);
    std::cout << "Running simulation for game3 with " << TURNS << " turns." << std::endl;
    game3.runSimulation(TURNS);

    std::cout << std::boolalpha;
    std::cout << "game1 == game2 board? " << (game1.getBoard() == game2.getBoard()) << std::endl;
    std::cout << "game1 == game3 board? " << (game1.getBoard() == game3.getBoard()) << std::endl;
    std::cout << "use_count: " << game1.getBoard().use_count() << std::endl;

    return 0;
}