#ifndef BOARDBUILDER_HPP
# define BOARDBUILDER_HPP
# include "Board.hpp"
# include <memory>

class BoardBuilder {
    private:
        Board _board;
    public:
        BoardBuilder();
        BoardBuilder(const BoardBuilder &other) = delete;
        BoardBuilder &operator=(const BoardBuilder &other) = delete;
        BoardBuilder(BoardBuilder &&other) noexcept = default;
        BoardBuilder &operator=(BoardBuilder &&other) noexcept = default;

        BoardBuilder &reset();
        Board build();

        BoardBuilder &addStartSquare();
        BoardBuilder &addJailSquare();
        BoardBuilder &addGoToJailSquare();
        BoardBuilder &addLuckSquare();
        BoardBuilder &addCommunitySquare();
        BoardBuilder &addParkingSquare();

        BoardBuilder &addPropertySquare(const std::string &name);
};

#endif