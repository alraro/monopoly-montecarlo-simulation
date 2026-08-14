#include "utils.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

unsigned int initRandom(unsigned int seed) {
    std::srand(seed);
    return seed;
}

unsigned int initRandom() {
    unsigned int seed = static_cast<unsigned int>(std::time(NULL));
    seed ^= static_cast<unsigned int>(getpid()) << 16;
    return initRandom(seed);
}

unsigned int rollGeneralDice(unsigned int numDice, unsigned int sidesPerDie) {
    if (sidesPerDie == 0)
        return 0;

    const unsigned int range = static_cast<unsigned int>(RAND_MAX) + 1u;
    const unsigned int limit = range - (range % sidesPerDie);

    unsigned int total = 0;
    for (unsigned int i = 0; i < numDice; ++i) {
        unsigned int roll;
        do {
            roll = static_cast<unsigned int>(std::rand());
        } while (roll >= limit);
        total += (roll % sidesPerDie) + 1;
    }
    return total;
}

MonopolyDiceRollResult rollMonopolyDice() {
    MonopolyDiceRollResult result;
    result.die1 = rollGeneralDice(1, 6);
    result.die2 = rollGeneralDice(1, 6);
    result.total = result.die1 + result.die2;
    result.doubles = result.die1 == result.die2;
    return result;
}
