#include "Board.hpp"
#include <iostream>

Board::Board(): _squares() {}

Board::~Board() {
    for (std::vector<BaseSquare *>::iterator it = _squares.begin(); it != _squares.end(); ++it) {
        delete *it;
    }
}

Board::Board(const Board &other): _squares() {
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
    }
    return *this;
}

void Board::addSquare(BaseSquare *square) {
    if (square != NULL) {
        this->_squares.push_back(square);
    }
}

void Board::printBoard() const {
    for (std::vector<BaseSquare *>::const_iterator it = _squares.begin(); it != _squares.end(); ++it) {
        std::cout << (*it)->getName() << " (Landed on: " << (*it)->getTimesLandedOn() << " times)" << std::endl;
    }
}
