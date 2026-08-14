#ifndef BOARDFACTORY_HPP
# define BOARDFACTORY_HPP
# include "Board.hpp"
# include <memory>

namespace BoardFactory {
    std::unique_ptr<Board> createDefaultBoard();
}

#endif