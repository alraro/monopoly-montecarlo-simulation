#ifndef UTILS_HPP
# define UTILS_HPP
# include <random>

unsigned int rollDice(unsigned int numDice, unsigned int sidesPerDie) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, sidesPerDie);

    unsigned int total = 0;
    for (unsigned int i = 0; i < numDice; ++i) {
        total += dis(gen);
    }
    return total;
}

#endif