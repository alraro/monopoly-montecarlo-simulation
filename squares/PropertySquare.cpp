#include "PropertySquare.hpp"

PropertySquare::PropertySquare(): BaseSquare("", 0) {}

PropertySquare::PropertySquare(const PropertySquare &other): BaseSquare(other) {}

PropertySquare &PropertySquare::operator=(const PropertySquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

PropertySquare::~PropertySquare() {}

PropertySquare::PropertySquare(std::string name): BaseSquare(name, 0) {}

EffectResult PropertySquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *PropertySquare::clone() const {
    return new PropertySquare(*this);
}