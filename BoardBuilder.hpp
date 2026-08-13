#ifndef BOARDBUILDER_HPP
# define BOARDBUILDER_HPP
# include "Board.hpp"

class BoardBuilder {
    private:
        Board *_board;
    public:
        BoardBuilder();
        BoardBuilder(const BoardBuilder &other);
        BoardBuilder &operator=(const BoardBuilder &other);
        ~BoardBuilder();

        BoardBuilder &reset();
        Board *build();

        BoardBuilder &addStartSquare();
        BoardBuilder &addJailSquare();
        BoardBuilder &addGoToJailSquare();
        BoardBuilder &addLuckSquare();
        BoardBuilder &addCommunitySquare();

        BoardBuilder &addPropertySquare(std::string name);
}

#endif