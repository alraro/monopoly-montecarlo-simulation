#include "GoToJailSquare.hpp"

GoToJailSquare::GoToJailSquare(): _name("Go to Jail"), _timesLandedOn(0), _jailSquareIndex(0), _jailSquare(NULL) {}

GoToJailSquare::GoToJailSquare(const GoToJailSquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn), _jailSquareIndex(other._jailSquareIndex), _jailSquare(other._jailSquare) {}

GoToJailSquare &GoToJailSquare::operator=(const GoToJailSquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
        _jailSquareIndex = other._jailSquareIndex;
        _jailSquare = other._jailSquare;
    }
    return *this;
}

GoToJailSquare::~GoToJailSquare() {}

EffectResult GoToJailSquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::GO_TO_JAIL;
    result.value = 0;
    return result;
}

BaseSquare *GoToJailSquare::clone() const {
    return new GoToJailSquare(*this);
}
