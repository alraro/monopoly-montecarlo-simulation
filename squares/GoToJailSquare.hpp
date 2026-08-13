#ifndef GOTOJAILSQUARE_HPP
# define GOTOJAILSQUARE_HPP
# include "BaseSquare.hpp"

class GoToJailSquare : public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        GoToJailSquare();
        GoToJailSquare(const GoToJailSquare &other);
        GoToJailSquare &operator=(const GoToJailSquare &other);
        virtual ~GoToJailSquare();

        virtual BaseSquare *clone() const;
}

#endif