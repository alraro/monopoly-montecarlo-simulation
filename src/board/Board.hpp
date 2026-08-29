#ifndef BOARD_HPP
# define BOARD_HPP
# include <vector>
# include "Squares.hpp"
# include "Types.hpp"

struct Board {
    std::vector<Square> squares;
    SquareId jailSquareIndex = 0;
};

#endif
