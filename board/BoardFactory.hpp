#ifndef BOARDFACTORY_HPP
# define BOARDFACTORY_HPP
# include "BoardBuilder.hpp"

class BoardFactory {
    private:
        BoardFactory();
        ~BoardFactory();
        BoardFactory(const BoardFactory &other);
        BoardFactory &operator=(const BoardFactory &other);
    public:
        static std::unique_ptr<Board> createDefaultBoard();
};

#endif