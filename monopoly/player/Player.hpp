#pragma once

#include <cstdint>
#include <monopoly/extra/Types.hpp>
#include <monopoly/extra/Rules.hpp>

namespace monopoly {

struct Player {
    PlayerId id;
    SquareId        currentSquare{0};
    int8_t          turnsLeftInJail{0}; // Maximum of 3 turns in jail, so int8_t is sufficient
    uint8_t         doublesRolledInARow{0}; // Maximum of 3 doubles in a row, so uint8_t is sufficient
    Money           currentMoney{rules::STARTING_MONEY};

    void sendToJail(SquareId jailSquareId) {
        currentSquare = jailSquareId;
        turnsLeftInJail = rules::TURNS_IN_JAIL;
        doublesRolledInARow = 0;
    }

    void moveToSquare(SquareId squareId) {
        currentSquare = squareId;
    }
};

}
