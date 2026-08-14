#include "JailSquare.hpp"

JailSquare::JailSquare(): BaseSquare("Jail", 0) {}

JailSquare::JailSquare(const JailSquare &other): BaseSquare(other) {}

JailSquare &JailSquare::operator=(const JailSquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

JailSquare::~JailSquare() {}

EffectResult JailSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

BaseSquare *JailSquare::clone() const {
    return new JailSquare(*this);
}