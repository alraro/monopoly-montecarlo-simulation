#ifndef UTILS_HPP
# define UTILS_HPP
# define TURNS_IN_JAIL 3

struct MonopolyDiceRollResult {
    unsigned int die1;
    unsigned int die2;
    unsigned int total;
    bool doubles;
};

void         initRandom();

unsigned int rollGeneralDice(unsigned int numDice, unsigned int sidesPerDie);

MonopolyDiceRollResult rollMonopolyDice();

bool rollForOutOfJailMonopoly();

#endif