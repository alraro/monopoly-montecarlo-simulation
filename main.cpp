#include "Game.hpp"

int main() {
    Game game;
    
    game.setDefaultBoard()
        .addPlayer("Alice")
        .addPlayer("Bob")
        .runSimulation(10000);
}