#ifndef PROPERTYSQUARE_HPP
# define PROPERTYSQUARE_HPP
# include "BaseSquare.hpp"

class PropertySquare : public BaseSquare {
    public:
        PropertySquare();

        PropertySquare(std::string name);

        std::unique_ptr<BaseSquare> clone() const override;
        EffectResult getSquareEffect(const Player &player) const override;
};

#endif