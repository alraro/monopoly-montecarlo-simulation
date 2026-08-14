#ifndef GAME_HPP
# define GAME_HPP
# include <vector>
# include "Board.hpp"
# include "Player.hpp"

class Game {
    private:
        Board *_board;
        std::vector<Player *> _players;
        unsigned int _currentPlayerIndex;
        void _showSquareLandingInfo();
    public:
        Game();
        Game(const Game &other);
        Game &operator=(const Game &other);
        ~Game();

        Game &clear();

        Game &addPlayer(const Player &player);
        Game &addPlayer(const std::string &name);
        Game &clearPlayers();

        Game &setBoard(const Board &board);
        Game &setDefaultBoard();
        Game &clearBoard();

        void runSimulation(unsigned int numTurns);
};

#endif