#include "JailSquare.hpp"

JailSquare::JailSquare(): _name("Jail"), _timesLandedOn(0) {}

JailSquare::JailSquare(const JailSquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn) {}

JailSquare &JailSquare::operator=(const JailSquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
    }
    return *this;
}

JailSquare::~JailSquare() {}

EffectResult JailSquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *JailSquare::clone() const {
    return new JailSquare(*this);
}