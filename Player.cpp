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