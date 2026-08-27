#ifndef PROPERTYSQUARE_HPP
# define PROPERTYSQUARE_HPP
# include "BaseSquare.hpp"

class PropertySquare : public BaseSquare {
    public:
        PropertySquare();

        PropertySquare(std::string name);

        EffectResult getSquareEffect(const Player &player) const override;
        std::unique_ptr<BaseSquare> clone() const override;
};

#endif