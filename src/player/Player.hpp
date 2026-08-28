#ifndef PLAYER_HPP
# define PLAYER_HPP
# include <string>
# include <memory>
# include "Strategy.hpp"
# include <vector>
# include <cstdint>

class Player {
    private:
        unsigned int                    _id;
        std::string                     _name;
        std::string                     _description;
        unsigned int                    _currentSquare;
        int                             _turnsLeftInJail;
        unsigned int                    _doublesRolledInARow;

        int64_t                         _currentMoney;
        std::vector<unsigned int>       _squaresOwned;
        Strategy&                       _strategy;
    public:
        Player(unsigned int id, const std::string &name, unsigned int startingSquare, int64_t startingMoney);
        void setCurrentSquare(unsigned int square);
        unsigned int getCurrentSquare() const;

        unsigned int getId() const;

        const std::string &getDescription() const;

        void setName(const std::string &name);
        const std::string &getName() const;

        void decrementTurnsLeftInJail();
        int getTurnsLeftInJail() const;
        void startTurnsLeftInJailCountdown();
        void resetTurnsLeftInJail();

        void incrementDoublesRolled();
        void resetDoublesRolled();
        unsigned int getDoublesRolledInARow() const;

        bool isInJail() const;

};

#endif