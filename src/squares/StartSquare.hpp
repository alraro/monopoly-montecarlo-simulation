#ifndef STARTSQUARE_HPP
# define STARTSQUARE_HPP
# include "BaseSquare.hpp"

class StartSquare : public BaseSquare {
    public:
        StartSquare();

        EffectResult getSquareEffect(const Player &player) const override;
};

#endif