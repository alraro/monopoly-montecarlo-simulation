#include "ParkingSquare.hpp"

ParkingSquare::ParkingSquare(): BaseSquare("Parking") {}

EffectResult ParkingSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}
