#ifndef JAILSQUARE_HPP
# define JAILSQUARE_HPP
# include "BaseSquare.hpp"

class JailSquare : public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        JailSquare();
        JailSquare(const JailSquare &other);
        JailSquare &operator=(const JailSquare &other);
        virtual ~JailSquare();
    
        virtual BaseSquare *clone() const;
};

#endif