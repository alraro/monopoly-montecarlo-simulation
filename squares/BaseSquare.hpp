#ifndef ISQUARE_HPP
# define ISQUARE_HPP
# include <string>
# include "effectType.hpp"

class Player;

class BaseSquare {
    private:
        std::string _name;
        unsigned int _timesLandedOn;
    protected:
        BaseSquare();
        BaseSquare(const BaseSquare &other);
        BaseSquare &operator=(const BaseSquare &other);

        virtual EffectResult getSquareEffect(const Player &player) const = 0;
    public:
        virtual ~BaseSquare() {};
        EffectResult landOn(const Player &player);

        int getTimesLandedOn() const;
        const std::string &getName() const;

        virtual BaseSquare *clone() const = 0;
}

#endif