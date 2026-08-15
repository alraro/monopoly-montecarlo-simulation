#ifndef STARTSQUARE_HPP
# define STARTSQUARE_HPP
# include "BaseSquare.hpp"

class StartSquare : public BaseSquare {
    public:
        StartSquare();

        std::unique_ptr<BaseSquare> clone() const override;
        EffectResult getSquareEffect(const Player &player) const override;
};

#endif