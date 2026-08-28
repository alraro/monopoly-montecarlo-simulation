#ifndef ISQUARE_HPP
# define ISQUARE_HPP
# include <string>
# include "effects.hpp"
# include <memory>

class Player;

class BaseSquare {
    private:
        std::string _name;
    protected:
        BaseSquare();
        BaseSquare(std::string name);

    public:
        virtual ~BaseSquare() = default;
        BaseSquare(const BaseSquare&) = default;
        BaseSquare& operator=(const BaseSquare&) = default;
        BaseSquare(BaseSquare&&) = default;
        BaseSquare& operator=(BaseSquare&&) = default;
        
        const std::string &getName() const;
        
        virtual SquareEffectResult getSquareEffect(const Player &player) const = 0;

        virtual std::unique_ptr<BaseSquare> clone() const = 0;
};

#endif