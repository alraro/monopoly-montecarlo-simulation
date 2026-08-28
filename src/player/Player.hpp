#ifndef PLAYER_HPP
# define PLAYER_HPP

struct Player {
    unsigned int id;
    unsigned int currentSquare;
    int turnsLeftInJail;
    unsigned int doublesRolledInARow;
    int64_t currentMoney;
};

#endif