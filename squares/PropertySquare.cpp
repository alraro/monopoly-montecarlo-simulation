#include "PropertySquare.hpp"

PropertySquare::PropertySquare(): BaseSquare("", 0) {}

PropertySquare::PropertySquare(std::string name): BaseSquare(name, 0) {}

EffectResult PropertySquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> PropertySquare::clone() const {
    return std::make_unique<PropertySquare>(*this);
}