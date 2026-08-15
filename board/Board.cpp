#include "Board.hpp"
#include <iostream>

Board::Board(): _squares(), _jailSquareIndex(0) {}

Board::Board(const Board &other): _squares(), _jailSquareIndex(other._jailSquareIndex) {
    _squares.reserve(other._squares.size());
    for (const auto &square : other._squares) {
        _squares.push_back(square->clone());
    }
}

Board &Board::operator=(const Board &other) {
    if (this != &other) {
        _squares.clear();
        _squares.reserve(other._squares.size());
        for (const auto &square : other._squares) {
            _squares.push_back(square->clone());
        }
        _jailSquareIndex = other._jailSquareIndex;
    }
    return *this;
}

void Board::addSquare(std::unique_ptr<BaseSquare> square) {
    if (square != nullptr) {
        this->_squares.push_back(std::move(square));
    }
}

void Board::printBoard() const {
    for (const auto &square : _squares) {
        std::cout << square->getName() << std::endl;
    }
}

BaseSquare *Board::getSquare(unsigned int index) const {
    if (index < _squares.size()) {
        return _squares[index].get();
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