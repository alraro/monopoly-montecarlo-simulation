#include "BaseSquare.hpp"

BaseSquare::BaseSquare(): _name("Default base square") {}

const std::string &BaseSquare::getName() const {
    return this->_name;
}

BaseSquare::BaseSquare(std::string name): _name(name) {}