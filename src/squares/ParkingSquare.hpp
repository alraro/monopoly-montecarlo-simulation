#ifndef PARKINGSQUARE_HPP
# define PARKINGSQUARE_HPP
# include "BaseSquare.hpp"

class ParkingSquare: public BaseSquare {
    public:
        ParkingSquare();

        SquareEffectResult getSquareEffect(const Player &player) const override;
        virtual std::unique_ptr<BaseSquare> clone() const override;
};

#endif