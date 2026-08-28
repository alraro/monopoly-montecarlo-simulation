#include "GoToJailSquare.hpp"

GoToJailSquare::GoToJailSquare(): BaseSquare("Go to Jail") {}

SquareEffectResult GoToJailSquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::GoToJail, 0};
}

std::unique_ptr<BaseSquare> GoToJailSquare::clone() const {
    return std::make_unique<GoToJailSquare>(*this);
}
