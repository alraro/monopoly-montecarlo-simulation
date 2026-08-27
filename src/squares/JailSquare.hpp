#ifndef JAILSQUARE_HPP
# define JAILSQUARE_HPP
# include "BaseSquare.hpp"

class JailSquare : public BaseSquare {
    public:
        JailSquare();

        EffectResult getSquareEffect(const Player &player) const override;
        virtual std::unique_ptr<BaseSquare> clone() const override;
};

#endif
