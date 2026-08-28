#ifndef LUCKSQUARE_HPP
# define LUCKSQUARE_HPP
# include "BaseSquare.hpp"

class LuckSquare : public BaseSquare {
    public:
        LuckSquare();

        SquareEffectResult getSquareEffect(const Player &player) const override;
        virtual std::unique_ptr<BaseSquare> clone() const override;
};

#endif