#ifndef BOARD_HPP
# define BOARD_HPP
# include <vector>

class Board {
    private:
        std::vector<BaseSquare *> _squares;
    public:
        Board();
        ~Board();
        Board(const Board &other);
        Board &operator=(const Board &other);

        void addSquare(BaseSquare *square);
        void printBoard() const;
}

#endif