#pragma once

#include <monopoly/board/Board.hpp>
# include <monopoly/player/Player.hpp>
# include <monopoly/extra/Effects.hpp>
# include <monopoly/game/GameStatistics.hpp>
# include <monopoly/simulation/SimulationConfig.hpp>
# include <monopoly/extra/Dice.hpp>
#include <string_view>
#include <atomic>

namespace monopoly {

class Game {
    private:
        std::atomic<bool>               &_shouldStop;
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
        std::ofstream _createStatsFile(std::string_view fileName) const;
        void _printStatistics() const;

    public:
        Game(const SimulationConfig &config, GameId gameId, std::atomic<bool> &shouldStop);

        void play();
};

Board getBoardFromRules(const SimulationConfig &config);
GameStatistics getGameStatisticsFromRules(const SimulationConfig &config);
std::vector<Player> getPlayersFromRules(const SimulationConfig &config);

}