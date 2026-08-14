#ifndef PROPERTYSQUARE_HPP
# define PROPERTYSQUARE_HPP
# include "BaseSquare.hpp"

class PropertySquare : public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        PropertySquare();
        PropertySquare(const PropertySquare &other);
        PropertySquare &operator=(const PropertySquare &other);
        virtual ~PropertySquare();

        PropertySquare(std::string name);

        virtual BaseSquare *clone() const;
};

#endif