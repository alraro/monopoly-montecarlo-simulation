#include "PropertySquare.hpp"

PropertySquare::PropertySquare(): BaseSquare("", 0) {}

PropertySquare::PropertySquare(std::string name): BaseSquare(name, 0) {}

EffectResult PropertySquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

std::unique_ptr<BaseSquare> PropertySquare::clone() const {
    return std::make_unique<PropertySquare>(*this);
}