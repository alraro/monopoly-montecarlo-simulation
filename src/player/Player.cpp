#include "Player.hpp"
#include "rules.hpp"

Player::Player(unsigned int id, const std::string &name, unsigned int currentSquare, int64_t startingMoney): 
                    _id(id),
                    _name(name),
                    _description("[ID: " + std::to_string(id) + ", Name: " + name + "]"),
                    _currentSquare(currentSquare),
                    _turnsLeftInJail(0),
                    _doublesRolledInARow(0),
                    _currentMoney(startingMoney),
                    _squaresOwned() {}

void Player::setCurrentSquare(unsigned int square) {
    _currentSquare = square;
}

unsigned int Player::getCurrentSquare() const {
    return _currentSquare;
}

const std::string &Player::getDescription() const {
    return _description;
}

unsigned int Player::getId() const {
    return _id;
}

void Player::setName(const std::string &name) {
    _name = name;
    _description = "[ID: " + std::to_string(_id) + ", Name: " + name + "]";
}

const std::string &Player::getName() const {
    return _name;
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
    _turnsLeftInJail = rules::TURNS_IN_JAIL;
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
