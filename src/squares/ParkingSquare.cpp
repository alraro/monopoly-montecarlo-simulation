#include "ParkingSquare.hpp"

ParkingSquare::ParkingSquare(): BaseSquare("Parking") {}

SquareEffectResult ParkingSquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::None, 0};
}

std::unique_ptr<BaseSquare> ParkingSquare::clone() const {
    return std::make_unique<ParkingSquare>(*this);
}