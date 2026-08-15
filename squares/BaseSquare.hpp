#ifndef ISQUARE_HPP
# define ISQUARE_HPP
# include <string>
# include "effectType.hpp"
# include <memory>

class Player;

class BaseSquare {
    private:
        std::string _name;
    protected:
        BaseSquare();
        BaseSquare(const BaseSquare &other);
        BaseSquare &operator=(const BaseSquare &other);
        BaseSquare(std::string name);

        virtual EffectResult getSquareEffect(const Player &player) const = 0;
    public:
        virtual ~BaseSquare() = default;
        EffectResult landOn(const Player &player);

        const std::string &getName() const;

        virtual std::unique_ptr<BaseSquare> clone() const = 0;
};

#endif