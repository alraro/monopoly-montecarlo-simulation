#include "utils.hpp"
#include "rules.hpp"
#include <random>

namespace {
    std::mt19937 &generator() {
        static std::mt19937 gen;
        return gen;
    }
}

unsigned int initRandom(unsigned int seed) {
    generator().seed(seed);
    return seed;
}

unsigned int initRandom() {
    std::random_device rd;
    return initRandom(rd());
}

unsigned int rollGeneralDice(unsigned int numDice, unsigned int sidesPerDie) {
    if (sidesPerDie == 0)
        return 0;

    std::uniform_int_distribution<unsigned int> die(1, sidesPerDie);

    unsigned int total = 0;
    for (unsigned int i = 0; i < numDice; ++i) {
        total += die(generator());
    }
    return total;
}

MonopolyDiceRollResult rollMonopolyDice() {
    MonopolyDiceRollResult result;
    result.die1 = rollGeneralDice(1, rules::DICE_SIDES);
    result.die2 = rollGeneralDice(1, rules::DICE_SIDES);
    result.total = result.die1 + result.die2;
    result.doubles = result.die1 == result.die2;
    return result;
}
