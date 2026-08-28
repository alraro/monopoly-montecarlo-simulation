#include "JailSquare.hpp"

JailSquare::JailSquare(): BaseSquare("Jail") {}

SquareEffectResult JailSquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::None, 0};
}

std::unique_ptr<BaseSquare> JailSquare::clone() const {
    return std::make_unique<JailSquare>(*this);
}
