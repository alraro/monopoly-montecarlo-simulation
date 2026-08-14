#include "Board.hpp"
#include <iostream>

Board::Board(): _squares(), _jailSquareIndex(0) {}

Board::~Board() {
    for (std::vector<BaseSquare *>::iterator it = _squares.begin(); it != _squares.end(); ++it) {
        delete *it;
    }
}

Board::Board(const Board &other): _squares(), _jailSquareIndex(other._jailSquareIndex) {
    for (std::vector<BaseSquare *>::const_iterator it = other._squares.begin(); it != other._squares.end(); ++it) {
        _squares.push_back((*it)->clone());
    }
}

Board &Board::operator=(const Board &other) {
    if (this != &other) {
        for (std::vector<BaseSquare *>::iterator it = _squares.begin(); it != _squares.end(); ++it) {
            delete *it;
        }
        _squares.clear();
        for (std::vector<BaseSquare *>::const_iterator it = other._squares.begin(); it != other._squares.end(); ++it) {
            _squares.push_back((*it)->clone());
        }
        _jailSquareIndex = other._jailSquareIndex;
    }
    return *this;
}

void Board::addSquare(BaseSquare *square) {
    if (square != nullptr) {
        this->_squares.push_back(square);
    }
}

void Board::printBoard() const {
    for (std::vector<BaseSquare *>::const_iterator it = _squares.begin(); it != _squares.end(); ++it) {
        std::cout << (*it)->getName() << " (Landed on: " << (*it)->getTimesLandedOn() << " times)" << std::endl;
    }
}

BaseSquare *Board::getSquare(unsigned int index) const {
    if (index < _squares.size()) {
        return _squares[index];
    } else {
        return nullptr;
    }
}

unsigned int Board::getJailSquareIndex() const {
    return _jailSquareIndex;
}

void Board::setJailSquareIndex(unsigned int index) {
    _jailSquareIndex = index;
}

unsigned int Board::getBoardSize() const {
    return _squares.size();
}