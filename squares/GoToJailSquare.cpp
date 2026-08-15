#include "GoToJailSquare.hpp"

GoToJailSquare::GoToJailSquare(): BaseSquare("Go to Jail") {}

EffectResult GoToJailSquare::getSquareEffect(const Player &) const {
    return {EffectType::GoToJail, 0};
}
