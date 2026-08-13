#ifndef LUCKSQUARE_HPP
# define LUCKSQUARE_HPP
# include "BaseSquare.hpp"

class LuckSquare : public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        LuckSquare();
        LuckSquare(const LuckSquare &other);
        LuckSquare &operator=(const LuckSquare &other);
        virtual ~LuckSquare();

        virtual BaseSquare *clone() const;
};

#endif