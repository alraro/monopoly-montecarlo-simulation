#include "JailSquare.hpp"

JailSquare::JailSquare(): BaseSquare("Jail") {}

EffectResult JailSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}
