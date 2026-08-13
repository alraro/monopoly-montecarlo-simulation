#include "StartSquare.hpp"

StartSquare::StartSquare(): _name("Start"), _timesLandedOn(0) {}

StartSquare::StartSquare(const StartSquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn) {}

StartSquare &StartSquare::operator=(const StartSquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
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