#ifndef PROPERTYSQUARE_HPP
# define PROPERTYSQUARE_HPP
# include "BaseSquare.hpp"

class PropertySquare : public BaseSquare {
    protected:
        EffectResult getSquareEffect(const Player &player) const override;
    public:
        PropertySquare();

        PropertySquare(std::string name);

        BaseSquare *clone() const override;
};

#endif