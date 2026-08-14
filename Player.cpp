#include "Player.hpp"
#include "utils.hpp"

Player::Player(): _name("Anonymous player"), _currentSquare(0), _turnsLeftInJail(0), _doublesRolledInARow(0) {}

Player::Player(std::string name, unsigned int currentSquare): _name(name), _currentSquare(currentSquare), _turnsLeftInJail(0), _doublesRolledInARow(0) {}

Player::Player(const Player &other): _name(other._name), _currentSquare(other._currentSquare), _turnsLeftInJail(other._turnsLeftInJail), _doublesRolledInARow(other._doublesRolledInARow) {}

Player &Player::operator=(const Player &other) {
    if (this != &other) {
        _name = other._name;
        _currentSquare = other._currentSquare;
        _turnsLeftInJail = other._turnsLeftInJail;
        _doublesRolledInARow = other._doublesRolledInARow;
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

void Player::setTurnsLeftInJail(int turns) {
    _turnsLeftInJail = turns;
}

int Player::getTurnsLeftInJail() const {
    return _turnsLeftInJail;
}

void Player::decrementTurnsLeftInJail() {
    if (_turnsLeftInJail > 0) {
        --_turnsLeftInJail;
    }
}

void Player::startTurnsLeftInJailCountdown() {
    _turnsLeftInJail = TURNS_IN_JAIL;
}

void Player::resetTurnsLeftInJail() {
    _turnsLeftInJail = 0;
}

void Player::incrementDoublesRolled() {
    ++_doublesRolledInARow;
}

void Player::resetDoublesRolled() {
    _doublesRolledInARow = 0;
}

unsigned int Player::getDoublesRolledInARow() const {
    return _doublesRolledInARow;
}

bool Player::isInJail() const {
    return _turnsLeftInJail > 0;
}
