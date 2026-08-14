#include "Player.hpp"

Player::Player(): _name("Anonymous player"), _currentSquare(0) {}

Player::Player(std::string name, unsigned int currentSquare): _name(name), _currentSquare(currentSquare) {}

Player::Player(const Player &other): _name(other._name), _currentSquare(other._currentSquare) {}

Player &Player::operator=(const Player &other) {
    if (this != &other) {
        _name = other._name;
        _currentSquare = other._currentSquare;
    }
    return *this;
}

Player::~Player() {}

void Player::setCurrentSquare(unsigned int square) {
    _currentSquare = square;
}

unsigned int Player::getCurrentSquare() const {
    return _currentSquare;
}

void Player::setName(const std::string &name) {
    _name = name;
}

const std::string &Player::getName() const {
    return _name;
}
