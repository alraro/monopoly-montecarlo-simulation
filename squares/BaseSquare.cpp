#include "BaseSquare.hpp"

BaseSquare::BaseSquare(): _name("Default base square"), _timesLandedOn(0) {}

BaseSquare::BaseSquare(const BaseSquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn) {}

BaseSquare &BaseSquare::operator=(const BaseSquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
    }
    return *this;
}

BaseSquare::~BaseSquare() {}

EffectResult BaseSquare::landOn(const Player &player) {
    ++(this->_timesLandedOn);
    return this->getSquareEffect(player);
}

int BaseSquare::getTimesLandedOn() const {
    return this->_timesLandedOn;
}

const std::string &BaseSquare::getName() const {
    return this->_name;
}