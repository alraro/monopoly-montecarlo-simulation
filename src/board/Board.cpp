#include "Board.hpp"
#include <iostream>

Board::Board(): _squares(), _jailSquareIndex(0) {}

Board &Board::clone() const {
    Board newBoard;
    for (const auto &square : _squares) {
        newBoard.addSquare(square->clone());
    }
    newBoard.setJailSquareIndex(_jailSquareIndex);
    return newBoard;
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

const BaseSquare &Board::getSquare(unsigned int index) const {
    if (index < _squares.size()) {
        return *_squares[index];
    } else {
        throw std::out_of_range("Index out of bounds");
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