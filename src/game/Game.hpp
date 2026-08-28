#ifndef GAME_HPP
# define GAME_HPP
# include <vector>
# include "Board.hpp"
# include "Player.hpp"
# include "effects.hpp"
# include "utils.hpp"
# include <memory>
# include "GameStatistics.hpp"
# include "SimulationRules.hpp"

class Game {
    private:
        const SimulationRules          &_rules;
        Board                           _board;
        std::vector<Player>             _players;
        unsigned int                    _currentPlayerIndex;
        GameStatistics                  _gameStatistics;

        void _showSquareLandingInfo() const;
        void _sendPlayerToJail(Player &player);

        SquareEffectResult _movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll);

        void _playPlayerTurn(Player &player);

        void _playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll);
        void _playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll);

        void _setupGameStatistics();

    public:
        Game(const SimulationRules &rules);

        void play(unsigned int numTurns);
        void printStatistics() const;
        void exportPlayersStatisticsToCSV(const std::string &filename) const;
        void exportSquaresStatisticsToCSV(const std::string &filename) const;
};

Board getBoardFromRules(const SimulationRules &rules);
GameStatistics getGameStatisticsFromRules(const SimulationRules &rules);
std::vector<Player> getPlayersFromRules(const SimulationRules &rules);

#endif