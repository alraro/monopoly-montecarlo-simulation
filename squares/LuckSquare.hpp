#ifndef LUCKSQUARE_HPP
# define LUCKSQUARE_HPP
# include "BaseSquare.hpp"

class LuckSquare : public BaseSquare {
    protected:
        EffectResult getSquareEffect(const Player &player) const override;
    public:
        LuckSquare();

        BaseSquare *clone() const override;
};

#endif