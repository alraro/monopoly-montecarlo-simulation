#include "BaseSquare.hpp"

BaseSquare::BaseSquare(): _name("Default base square") {}

BaseSquare::BaseSquare(const BaseSquare &other): _name(other._name) {}

BaseSquare &BaseSquare::operator=(const BaseSquare &other) {
    if (this != &other) {
        _name = other._name;
    }
    return *this;
}

EffectResult BaseSquare::landOn(const Player &player) {
    return this->getSquareEffect(player);
}

const std::string &BaseSquare::getName() const {
    return this->_name;
}

BaseSquare::BaseSquare(std::string name): _name(name) {}