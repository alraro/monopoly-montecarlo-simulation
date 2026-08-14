#include "BoardBuilder.hpp"
#include "StartSquare.hpp"
#include "JailSquare.hpp"
#include "GoToJailSquare.hpp"
#include "LuckSquare.hpp"
#include "CommunitySquare.hpp"
#include "PropertySquare.hpp"

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

const Board &BoardBuilder::getBoard() const {
    return *_board;
}

BoardBuilder &BoardBuilder::addStartSquare() {
    _board->addSquare(new StartSquare());
    return *this;
}

BoardBuilder &BoardBuilder::addJailSquare() {
    _board->addSquare(new JailSquare());
    _board->setJailSquareIndex(_board->getBoardSize() - 1);
    return *this;
}

BoardBuilder &BoardBuilder::addGoToJailSquare() {
    _board->addSquare(new GoToJailSquare());
    return *this;
}

BoardBuilder &BoardBuilder::addLuckSquare() {
    _board->addSquare(new LuckSquare());
    return *this;
}

BoardBuilder &BoardBuilder::addCommunitySquare() {
    _board->addSquare(new CommunitySquare());
    return *this;
}

BoardBuilder &BoardBuilder::addPropertySquare(const std::string &name) {
    _board->addSquare(new PropertySquare(name));
    return *this;
}