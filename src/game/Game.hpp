#ifndef GAME_HPP
# define GAME_HPP
# include "Board.hpp"
# include "Player.hpp"
# include "effects.hpp"
# include "GameStatistics.hpp"
# include "SimulationConfig.hpp"
# include "Dice.hpp"
#include <filesystem>
#include <string_view>

class Game {
    private:
        const SimulationConfig          &_config;
        GameId                          _gameId;
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
        void _exportPlayersStatisticsToCSV(std::string_view fileName = "player_stats.csv") const;
        void _exportSquaresStatisticsToCSV(std::string_view fileName = "square_stats.csv") const;
        std::filesystem::path _createGameStatsDirectory() const;
        void _printStatistics() const;

    public:
        Game(const SimulationConfig &config, GameId gameId);

        void play(size_t numTurns);
};

Board getBoardFromRules(const SimulationConfig &config);
GameStatistics getGameStatisticsFromRules(const SimulationConfig &config);
std::vector<Player> getPlayersFromRules(const SimulationConfig &config);

#endif