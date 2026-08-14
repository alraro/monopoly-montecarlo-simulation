#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): BaseSquare("Community", 0) {}

EffectResult CommunitySquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

BaseSquare *CommunitySquare::clone() const {
    return new CommunitySquare(*this);
}