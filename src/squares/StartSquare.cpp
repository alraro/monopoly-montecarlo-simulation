#include "StartSquare.hpp"

StartSquare::StartSquare(): BaseSquare("Start") {}

SquareEffectResult StartSquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::None, 0};
}

std::unique_ptr<BaseSquare> StartSquare::clone() const {
    return std::make_unique<StartSquare>(*this);
}