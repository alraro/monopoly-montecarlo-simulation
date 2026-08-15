#ifndef JAILSQUARE_HPP
# define JAILSQUARE_HPP
# include "BaseSquare.hpp"

class JailSquare : public BaseSquare {
    public:
        JailSquare();

        std::unique_ptr<BaseSquare> clone() const override;
        EffectResult getSquareEffect(const Player &player) const override;
};

#endif
