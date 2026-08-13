#include "StartSquare.hpp"

StartSquare::StartSquare(): BaseSquare("Start", 0) {}

StartSquare::StartSquare(const StartSquare &other): BaseSquare(other) {}

StartSquare &StartSquare::operator=(const StartSquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

StartSquare::~StartSquare() {}

EffectResult StartSquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *StartSquare::clone() const {
    return new StartSquare(*this);
}