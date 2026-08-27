#include "PropertySquare.hpp"

PropertySquare::PropertySquare(): BaseSquare("Generic property") {}

PropertySquare::PropertySquare(std::string name): BaseSquare(name) {}

EffectResult PropertySquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> PropertySquare::clone() const {
    return std::make_unique<PropertySquare>(*this);
}