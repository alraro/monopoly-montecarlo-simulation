#include "JailSquare.hpp"

JailSquare::JailSquare(): BaseSquare("Jail", 0) {}

EffectResult JailSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

std::unique_ptr<BaseSquare> JailSquare::clone() const {
    return std::make_unique<JailSquare>(*this);
}