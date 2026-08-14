#ifndef PLAYER_HPP
# define PLAYER_HPP
# include <string>

class Player {
    private:
        std::string _name;
        unsigned int _currentSquare;
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

};

#endif