#ifndef PARKINGSQUARE_HPP
# define PARKINGSQUARE_HPP
# include "BaseSquare.hpp"

class ParkingSquare: public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        ParkingSquare();
        ~ParkingSquare();
        ParkingSquare(const ParkingSquare &other);
        ParkingSquare &operator=(const ParkingSquare &other);

        virtual BaseSquare *clone() const;
};

#endif