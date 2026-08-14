#ifndef PLAYER_HPP
# define PLAYER_HPP
# include <string>

class Player {
    private:
        std::string _name;
        unsigned int _currentSquare;
        int _turnsLeftInJail;
        unsigned int _doublesRolledInARow;
    public:
        Player();
        virtual ~Player();
        Player(const Player &other);
        Player &operator=(const Player &other);

        Player(std::string name, unsigned int currentSquare);
        void setCurrentSquare(unsigned int square);
        unsigned int getCurrentSquare() const;

        void setName(const std::string &name);
        const std::string &getName() const;

        void setTurnsLeftInJail(int turns);
        void decrementTurnsLeftInJail();
        int getTurnsLeftInJail() const;
        void getJailed();

        void incrementDoublesRolled();
        void resetDoublesRolled();
        unsigned int getDoublesRolledInARow() const;

        bool isInJail() const;

};

#endif