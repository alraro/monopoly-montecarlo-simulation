#include "BoardFactory.hpp"

BoardFactory::BoardFactory() {}

BoardFactory::~BoardFactory() {}

BoardFactory::BoardFactory(const BoardFactory &other) {
    (void)other;
}

BoardFactory &BoardFactory::operator=(const BoardFactory &other) {
    (void)other;
    return *this;
}

Board &BoardFactory::createDefaultBoard() {
    BoardBuilder builder;
    return builder.reset()
        .addStartSquare()
        .addJailSquare()
        .addGoToJailSquare()
        .addLuckSquare()
        .addCommunitySquare()
        .addPropertySquare("Mediterranean Avenue")
        .addPropertySquare("Baltic Avenue")
        .getBoard();
}
