#include "utils.hpp"
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

void initRandom() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
}

unsigned int rollDice(unsigned int numDice, unsigned int sidesPerDie) {
    if (sidesPerDie == 0)
        return 0;

    unsigned int total = 0;
    for (unsigned int i = 0; i < numDice; ++i) {
        // En C++98: (rand() % LADOS) genera un rango de [0 a LADOS-1].
        // Le sumamos 1 para que sea de [1 a LADOS].
        total += (std::rand() % sidesPerDie) + 1;
    }
    return total;
}