#include "BoardBuilder.hpp"
#include "StartSquare.hpp"
#include "JailSquare.hpp"
#include "GoToJailSquare.hpp"
#include "LuckSquare.hpp"
#include "CommunitySquare.hpp"
#include "PropertySquare.hpp"
#include "ParkingSquare.hpp"
#include <memory>

BoardBuilder::BoardBuilder(): _board(Board()) {}

BoardBuilder &BoardBuilder::reset() {
    _board = Board();
    return *this;
}

Board BoardBuilder::build() {
    Board builtBoard = std::move(_board);
    reset();
    return builtBoard;
}

BoardBuilder &BoardBuilder::addStartSquare() {
    _board.addSquare(std::make_unique<StartSquare>());
    return *this;
}

BoardBuilder &BoardBuilder::addJailSquare() {
    _board.addSquare(std::make_unique<JailSquare>());
    _board.setJailSquareIndex(_board.getBoardSize() - 1);
    return *this;
}

BoardBuilder &BoardBuilder::addGoToJailSquare() {
    _board.addSquare(std::make_unique<GoToJailSquare>());
    return *this;
}

BoardBuilder &BoardBuilder::addLuckSquare() {
    _board.addSquare(std::make_unique<LuckSquare>());
    return *this;
}

BoardBuilder &BoardBuilder::addCommunitySquare() {
    _board.addSquare(std::make_unique<CommunitySquare>());
    return *this;
}

BoardBuilder &BoardBuilder::addPropertySquare(const std::string &name) {
    _board.addSquare(std::make_unique<PropertySquare>(name));
    return *this;
}

BoardBuilder &BoardBuilder::addParkingSquare() {
    _board.addSquare(std::make_unique<ParkingSquare>());
    return *this;
}