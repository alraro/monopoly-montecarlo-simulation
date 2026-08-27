#ifndef UTILS_HPP
# define UTILS_HPP

struct MonopolyDiceRollResult {
    unsigned int die1;
    unsigned int die2;
    unsigned int total;
    bool doubles;
};

unsigned int initRandom();
unsigned int initRandom(unsigned int seed);

unsigned int rollGeneralDice(unsigned int numDice, unsigned int sidesPerDie);

MonopolyDiceRollResult rollMonopolyDice();

#endif