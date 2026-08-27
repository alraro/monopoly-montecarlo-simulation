#include "StartSquare.hpp"

StartSquare::StartSquare(): BaseSquare("Start") {}

EffectResult StartSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}
