#include "StartSquare.hpp"

StartSquare::StartSquare(): BaseSquare("Start") {}

EffectResult StartSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> StartSquare::clone() const {
    return std::make_unique<StartSquare>(*this);
}