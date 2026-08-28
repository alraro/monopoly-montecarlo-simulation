#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): BaseSquare("Luck") {}

SquareEffectResult LuckSquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::None, 0};
}

std::unique_ptr<BaseSquare> LuckSquare::clone() const {
    return std::make_unique<LuckSquare>(*this);
}