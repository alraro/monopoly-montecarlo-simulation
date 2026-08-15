#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): BaseSquare("Luck") {}

EffectResult LuckSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> LuckSquare::clone() const {
    return std::make_unique<LuckSquare>(*this);
}