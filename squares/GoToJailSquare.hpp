#ifndef GOTOJAILSQUARE_HPP
# define GOTOJAILSQUARE_HPP
# include "BaseSquare.hpp"

class GoToJailSquare : public BaseSquare {
    protected:
        EffectResult getSquareEffect(const Player &player) const override;
    public:
        GoToJailSquare();

        BaseSquare *clone() const override;
};

#endif