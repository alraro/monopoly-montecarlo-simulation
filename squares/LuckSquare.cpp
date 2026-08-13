#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): _name("Luck"), _timesLandedOn(0) {}

LuckSquare::LuckSquare(const LuckSquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn) {}

LuckSquare &LuckSquare::operator=(const LuckSquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
    }
    return *this;
}

LuckSquare::~LuckSquare() {}

EffectResult LuckSquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *LuckSquare::clone() const {
    return new LuckSquare(*this);
}