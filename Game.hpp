#ifndef GAME_HPP
# define GAME_HPP
# include <vector>
# include "Board.hpp"
# include "Player.hpp"
# include "effectType.hpp"
# include "utils.hpp"

class Game {
    private:
        Board *_board;
        std::vector<Player *> _players;
        unsigned int _currentPlayerIndex;
        void _showSquareLandingInfo();
        void _sendPlayerToJail(Player &player);

        EffectResult _movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll);

        void _playPlayerTurn(Player &player);

        void _playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll);
        void _playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll);
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