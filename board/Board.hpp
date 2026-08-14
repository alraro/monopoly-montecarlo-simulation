#ifndef BOARD_HPP
# define BOARD_HPP
# include <vector>
# include "BaseSquare.hpp"

class Board {
    private:
        std::vector<BaseSquare *> _squares;
        unsigned int _jailSquareIndex;
    public:
        Board();
        ~Board();
        Board(const Board &other);
        Board &operator=(const Board &other);

        void addSquare(BaseSquare *square);
        void printBoard() const;
        BaseSquare *getSquare(unsigned int index) const;

        unsigned int getJailSquareIndex() const;
        void setJailSquareIndex(unsigned int index);

        unsigned int getBoardSize() const;
};

#endif