#ifndef PLAYER_HPP
# define PLAYER_HPP
# include <string>

class Player {
    private:
        unsigned int _id;
        std::string _name;
        unsigned int _currentSquare;
        int _turnsLeftInJail;
        unsigned int _doublesRolledInARow;
    public:
        Player(const Player &other);
        Player &operator=(const Player &other);

        Player(unsigned int id, const std::string &name, unsigned int currentSquare);
        void setCurrentSquare(unsigned int square);
        unsigned int getCurrentSquare() const;

        unsigned int getId() const;

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