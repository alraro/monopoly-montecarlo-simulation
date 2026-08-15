#ifndef GOTOJAILSQUARE_HPP
# define GOTOJAILSQUARE_HPP
# include "BaseSquare.hpp"

class GoToJailSquare : public BaseSquare {
    public:
        GoToJailSquare();

        std::unique_ptr<BaseSquare> clone() const override;
        EffectResult getSquareEffect(const Player &player) const override;
};

#endif