#include "PropertySquare.hpp"

PropertySquare::PropertySquare(): BaseSquare("Generic property") {}

PropertySquare::PropertySquare(std::string name): BaseSquare(name) {}

SquareEffectResult PropertySquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::None, 0};
}

std::unique_ptr<BaseSquare> PropertySquare::clone() const {
    return std::make_unique<PropertySquare>(*this);
}