#ifndef GAME_HPP
# define GAME_HPP
# include <vector>
# include "Board.hpp"
# include "Player.hpp"
# include "effectType.hpp"
# include "utils.hpp"
# include <memory>
# include "GameStatistics.hpp"

class Game {
    private:
        std::shared_ptr<const Board>    _board;
        std::vector<Player>             _players;
        unsigned int                    _currentPlayerIndex;
        GameStatistics                  _gameStatistics;

        void _showSquareLandingInfo() const;
        void _sendPlayerToJail(Player &player);

        EffectResult _movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll);

        void _playPlayerTurn(Player &player);

        void _playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll);
        void _playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll);

        void _setupGameStatistics();

        void _printStatistics() const;
    public:
        Game();

        Game &clear();

        Game &addPlayer(const Player &player);
        Game &addPlayer(const std::string &name);
        Game &clearPlayers();

        Game &setBoard(std::shared_ptr<const Board> board);
        Game &setDefaultBoard();
        Game &clearBoard();
        const std::shared_ptr<const Board> &getBoard() const;

        void runSimulation(unsigned int numTurns);
};

#endif