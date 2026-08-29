#ifndef GAMESTATISTICS_HPP
# define GAMESTATISTICS_HPP
# include <vector>
# include "Types.hpp"

class GameStatistics {
    private:
        std::vector<PlayerStats>    _playerStats;
        std::vector<StatCount>      _squareLandings;
    public:
        GameStatistics() = default;

        void recordTurnInJailPlayer(PlayerId playerIndex) {
            ++_playerStats[playerIndex].turnsSpentInJail;
        }

        void recordTimesJailedPlayer(PlayerId playerIndex) {
            ++_playerStats[playerIndex].timesJailed;
        }

        void recordTurnPlayer(PlayerId playerIndex) {
            ++_playerStats[playerIndex].totalTurns;
        }

        void recordDiceRollPlayer(PlayerId playerIndex, MonopolyDiceRollResult diceRoll) {
            ++_playerStats[playerIndex].totalDiceRolls;
            if (diceRoll.areDoubles()) {
                ++_playerStats[playerIndex].totalDoublesRolled;
            }
        };

        void recordLandingSquare(PlayerId squareIndex) {
            ++_squareLandings[squareIndex];
        }
        
        const PlayerStats& getPlayerStats(PlayerId playerIndex) const {
            return _playerStats[playerIndex];
        }

        const std::vector<StatCount>& getSquareLandings() const {
            return _squareLandings;
        }

        const std::vector<PlayerStats>& getAllPlayerStats() const {
            return _playerStats;
        }

        const std::vector<StatCount>& getAllSquareLandings() const {
            return _squareLandings;
        }
};

#endif