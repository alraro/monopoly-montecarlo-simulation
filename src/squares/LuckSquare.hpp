#ifndef LUCKSQUARE_HPP
# define LUCKSQUARE_HPP
# include "BaseSquare.hpp"

class LuckSquare : public BaseSquare {
    public:
        LuckSquare();

        EffectResult getSquareEffect(const Player &player) const override;
};

#endif