#include "GoToJailSquare.hpp"

GoToJailSquare::GoToJailSquare(): BaseSquare("Go to Jail", 0) {}

EffectResult GoToJailSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = GO_TO_JAIL;
    result.value = 0;
    return result;
}

BaseSquare *GoToJailSquare::clone() const {
    return new GoToJailSquare(*this);
}
