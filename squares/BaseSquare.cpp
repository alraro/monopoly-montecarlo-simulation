#include "BaseSquare.hpp"

BaseSquare::BaseSquare(): _name("Default base square") {}

BaseSquare::BaseSquare(const BaseSquare &other): _name(other._name) {}

BaseSquare &BaseSquare::operator=(const BaseSquare &other) {
    if (this != &other) {
        _name = other._name;
    }
    return *this;
}

const std::string &BaseSquare::getName() const {
    return this->_name;
}

BaseSquare::BaseSquare(std::string name): _name(name) {}