#ifndef STARTSQUARE_HPP
# define STARTSQUARE_HPP
# include "BaseSquare.hpp"

class StartSquare : public BaseSquare {
    public:
        StartSquare();

        SquareEffectResult getSquareEffect(const Player &player) const override;
        std::unique_ptr<BaseSquare> clone() const override;
};

#endif