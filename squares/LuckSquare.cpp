#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): BaseSquare("Luck", 0) {}

EffectResult LuckSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

BaseSquare *LuckSquare::clone() const {
    return new LuckSquare(*this);
}