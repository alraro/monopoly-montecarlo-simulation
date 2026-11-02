#pragma once

#include <vector>
#include <monopoly/squares/Squares.hpp>
#include <monopoly/extra/Types.hpp>

namespace monopoly {

struct Board {
    std::vector<Square> squares;
    SquareId jailSquareIndex = 0;
};

}