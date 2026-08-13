#ifndef STARTSQUARE_HPP
# define STARTSQUARE_HPP
# include "BaseSquare.hpp"

class StartSquare : public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        StartSquare();
        StartSquare(const StartSquare &other);
        StartSquare &operator=(const StartSquare &other);
        virtual ~StartSquare();
        virtual BaseSquare *clone() const;
}

#endif