#include "LuckSquare.hpp"

LuckSquare::LuckSquare(): BaseSquare("Luck", 0) {}

LuckSquare::LuckSquare(const LuckSquare &other): BaseSquare(other) {}

LuckSquare &LuckSquare::operator=(const LuckSquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

LuckSquare::~LuckSquare() {}

EffectResult LuckSquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *LuckSquare::clone() const {
    return new LuckSquare(*this);
}