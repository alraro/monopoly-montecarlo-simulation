#include "Game.hpp"
#include "utils.hpp"

int main() {
    initRandom();
    Game game;

    game.setDefaultBoard()
        .addPlayer("Alice")
        .addPlayer("Bob")
        .runSimulation(10000);
}