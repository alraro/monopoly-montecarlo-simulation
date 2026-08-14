#include "ParkingSquare.hpp"

ParkingSquare::ParkingSquare(): BaseSquare("Parking", 0) {}

ParkingSquare::ParkingSquare(const ParkingSquare &other): BaseSquare(other) {}

ParkingSquare &ParkingSquare::operator=(const ParkingSquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

ParkingSquare::~ParkingSquare() {}

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