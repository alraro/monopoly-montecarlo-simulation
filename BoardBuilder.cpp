#include "BoardBuilder.hpp"

BoardBuilder::BoardBuilder(): _board(new Board()) {}

BoardBuilder::BoardBuilder(const BoardBuilder &other) {
    if (other._board != NULL) {
        this->_board = new Board(*other._board);
    } else {
        this->_board = NULL;
    }
}

BoardBuilder &BoardBuilder::operator=(const BoardBuilder &other) {
    if (this != &other) {
        delete _board;

        if (other._board != NULL) {
            this->_board = new Board(*other._board);
        } else {
            this->_board = NULL;
        }
    }
    return *this;
}

BoardBuilder::~BoardBuilder() {
    delete _board;
}

BoardBuilder &BoardBuilder::reset() {
    delete _board;
    _board = new Board();
    return *this;
}

Board *BoardBuilder::build() {
    return _board;
}

BoardBuilder &BoardBuilder::addStartSquare();
BoardBuilder &BoardBuilder::addJailSquare();
BoardBuilder &BoardBuilder::addGoToJailSquare();
BoardBuilder &BoardBuilder::addLuckSquare();
BoardBuilder &BoardBuilder::addCommunitySquare();

BoardBuilder &BoardBuilder::addPropertySquare(std::string name);