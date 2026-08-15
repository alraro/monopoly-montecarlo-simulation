#include "GoToJailSquare.hpp"

GoToJailSquare::GoToJailSquare(): BaseSquare("Go to Jail") {}

EffectResult GoToJailSquare::getSquareEffect(const Player &) const {
    return {EffectType::GoToJail, 0};
}

std::unique_ptr<BaseSquare> GoToJailSquare::clone() const {
    return std::make_unique<GoToJailSquare>(*this);
}
