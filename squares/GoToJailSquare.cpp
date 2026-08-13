#include "GoToJailSquare.hpp"

GoToJailSquare::GoToJailSquare(): BaseSquare("Go to Jail", 0) {}

GoToJailSquare::GoToJailSquare(const GoToJailSquare &other): BaseSquare(other) {}

GoToJailSquare &GoToJailSquare::operator=(const GoToJailSquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

GoToJailSquare::~GoToJailSquare() {}

EffectResult GoToJailSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = EffectType::GO_TO_JAIL;
    result.value = 0;
    return result;
}

BaseSquare *GoToJailSquare::clone() const {
    return new GoToJailSquare(*this);
}
