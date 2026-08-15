#ifndef LUCKSQUARE_HPP
# define LUCKSQUARE_HPP
# include "BaseSquare.hpp"

class LuckSquare : public BaseSquare {
    public:
        LuckSquare();

        std::unique_ptr<BaseSquare> clone() const override;
        EffectResult getSquareEffect(const Player &player) const override;
};

#endif