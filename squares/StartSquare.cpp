#include "StartSquare.hpp"

StartSquare::StartSquare(): BaseSquare("Start", 0) {}

EffectResult StartSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

std::unique_ptr<BaseSquare> StartSquare::clone() const {
    return std::make_unique<StartSquare>(*this);
}