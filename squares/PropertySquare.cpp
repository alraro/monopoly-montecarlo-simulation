#include "PropertySquare.hpp"

PropertySquare::PropertySquare(): _name(""), _timesLandedOn(0) {}

PropertySquare::PropertySquare(const PropertySquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn) {}

PropertySquare &PropertySquare::operator=(const PropertySquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
    }
    return *this;
}

PropertySquare::~PropertySquare() {}

PropertySquare::PropertySquare(std::string name): _name(name), _timesLandedOn(0) {}

EffectResult PropertySquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *PropertySquare::clone() const {
    return new PropertySquare(*this);
}