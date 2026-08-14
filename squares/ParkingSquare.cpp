#include "ParkingSquare.hpp"

ParkingSquare::ParkingSquare(): BaseSquare("Parking", 0) {}

EffectResult ParkingSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

BaseSquare *ParkingSquare::clone() const {
    return new ParkingSquare(*this);
}