#include "ParkingSquare.hpp"

ParkingSquare::ParkingSquare(): BaseSquare("Parking", 0) {}

EffectResult ParkingSquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> ParkingSquare::clone() const {
    return std::make_unique<ParkingSquare>(*this);
}