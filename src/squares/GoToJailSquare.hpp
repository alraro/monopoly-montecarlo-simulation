#ifndef GOTOJAILSQUARE_HPP
# define GOTOJAILSQUARE_HPP
# include "BaseSquare.hpp"

class GoToJailSquare : public BaseSquare {
    public:
        GoToJailSquare();

        EffectResult getSquareEffect(const Player &player) const override;
};

#endif