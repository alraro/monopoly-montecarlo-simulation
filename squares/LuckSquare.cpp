#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): BaseSquare("Luck") {}

EffectResult LuckSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}
