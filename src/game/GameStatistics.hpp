#ifndef GAMESTATISTICS_HPP
# define GAMESTATISTICS_HPP
# include <vector>
# include "utils.hpp"

class GameStatistics {
    private:
        std::vector<unsigned int> _turnsSpentInJailPerPlayer;
        std::vector<unsigned int> _timesJailedPerPlayer;
        std::vector<unsigned int> _totalTurnsPerPlayer;
        std::vector<unsigned int> _totalDoublesRolledPerPlayer;
        std::vector<unsigned int> _totalDiceRollsPerPlayer;
        std::vector<unsigned int> _totalLandingsPerSquare;
    public:
        GameStatistics();

        void setPlayerCount(unsigned int numPlayers);
        void setSquareCount(unsigned int numSquares);

        void recordTurnInJailPlayer(unsigned int playerIndex);
        unsigned int getTurnsSpentInJailPlayer(unsigned int playerIndex) const;

        void recordTimesJailedPlayer(unsigned int playerIndex);
        unsigned int getTimesJailedPlayer(unsigned int playerIndex) const;

        void recordTurnPlayer(unsigned int playerIndex);
        unsigned int getTotalTurnsPlayer(unsigned int playerIndex) const;

        void recordDiceRollPlayer(unsigned int playerIndex, MonopolyDiceRollResult diceRoll);
        unsigned int getTotalDiceRollsPlayer(unsigned int playerIndex) const;
        unsigned int getTotalDoublesRolledPlayer(unsigned int playerIndex) const;

        void recordLandingSquare(unsigned int squareIndex);
        unsigned int getTotalLandingsSquare(unsigned int squareIndex) const;

};

#endif