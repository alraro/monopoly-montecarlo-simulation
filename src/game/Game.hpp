#ifndef GAME_HPP
# define GAME_HPP
# include "Board.hpp"
# include "Player.hpp"
# include "effects.hpp"
# include "GameStatistics.hpp"
# include "SimulationConfig.hpp"
# include "Dice.hpp"

class Game {
    private:
        const SimulationConfig          &_config;
        Board                           _board;
        std::vector<Player>             _players;
        PlayerId                        _currentPlayerIndex;
        GameStatistics                  _gameStatistics;
        Dice                            _dice;

        void _showSquareLandingInfo() const;
        void _sendPlayerToJail(Player &player);

        SquareEffectResult _movePlayerDiceRoll(Player &player, MonopolyDiceRollResult diceRoll);

        void _playPlayerTurn(Player &player);

        void _playPlayerTurnDoubles(Player &player, MonopolyDiceRollResult diceRoll);
        void _playPlayerTurnNoDoubles(Player &player, MonopolyDiceRollResult diceRoll);

        void _setupGameStatistics();

    public:
        Game(const SimulationConfig &config);

        void play(size_t numTurns);
        void printStatistics() const;
        void exportPlayersStatisticsToCSV(const std::string &filename) const;
        void exportSquaresStatisticsToCSV(const std::string &filename) const;
};

Board getBoardFromRules(const SimulationConfig &config);
GameStatistics getGameStatisticsFromRules(const SimulationConfig &config);
std::vector<Player> getPlayersFromRules(const SimulationConfig &config);

#endif