#include "JailSquare.hpp"

JailSquare::JailSquare(): BaseSquare("Jail") {}

EffectResult JailSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> JailSquare::clone() const {
    return std::make_unique<JailSquare>(*this);
}