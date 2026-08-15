#ifndef PARKINGSQUARE_HPP
# define PARKINGSQUARE_HPP
# include "BaseSquare.hpp"

class ParkingSquare: public BaseSquare {
    public:
        ParkingSquare();

        std::unique_ptr<BaseSquare> clone() const override;
        EffectResult getSquareEffect(const Player &player) const override;
};

#endif