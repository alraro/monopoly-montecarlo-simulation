#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): BaseSquare("Luck", 0) {}

EffectResult LuckSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

std::unique_ptr<BaseSquare> LuckSquare::clone() const {
    return std::make_unique<LuckSquare>(*this);
}