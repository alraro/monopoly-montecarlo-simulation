#include "Board.hpp"
#include "Logger.hpp"

Board::Board(): _squares(), _jailSquareIndex(0) {}

Board::Board(const Board &other): _squares(), _jailSquareIndex(other._jailSquareIndex) {
    for (const auto &square : other._squares) {
        _squares.push_back(square->clone());
    }
}

Board& Board::operator=(const Board &other) {
    Board tmp(other);
    std::swap(_squares, tmp._squares);
    std::swap(_jailSquareIndex, tmp._jailSquareIndex);
    return *this;
}

void Board::addSquare(std::unique_ptr<BaseSquare> square) {
    if (square != nullptr) {
        this->_squares.push_back(std::move(square));
    }
}

void Board::printBoard() const {
    for (const auto &square : _squares) {
        Logger::info("Square: ", square->getName());
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