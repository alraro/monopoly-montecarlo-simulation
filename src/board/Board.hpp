#ifndef BOARD_HPP
# define BOARD_HPP
# include <vector>
# include "Squares.hpp"

struct Board {
    std::vector<Square> squares;
    unsigned int jailSquareIndex;
};

#endif
