#ifndef BOARD_HPP
# define BOARD_HPP
# include <vector>
# include "BaseSquare.hpp"
# include <memory>

class Board {
    private:
        std::vector<std::unique_ptr<BaseSquare>> _squares;
        unsigned int _jailSquareIndex;
    public:
        Board();
        Board(const Board &other);
        Board &operator=(const Board &other);
        Board(Board &&other) noexcept = default;
        Board &operator=(Board &&other) noexcept = default;

        void addSquare(std::unique_ptr<BaseSquare> square);
        void printBoard() const;
        BaseSquare *getSquare(unsigned int index) const;

        unsigned int getJailSquareIndex() const;
        void setJailSquareIndex(unsigned int index);

        unsigned int getBoardSize() const;
};

#endif