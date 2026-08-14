#ifndef STARTSQUARE_HPP
# define STARTSQUARE_HPP
# include "BaseSquare.hpp"

class StartSquare : public BaseSquare {
    protected:
        EffectResult getSquareEffect(const Player &player) const override;
    public:
        StartSquare();

        BaseSquare *clone() const override;
};

#endif