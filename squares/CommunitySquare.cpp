#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): BaseSquare("Community", 0) {}

EffectResult CommunitySquare::getSquareEffect(const Player &player) const {
    (void)player; // Unused parameter

    EffectResult result;
    result.type = NONE;
    result.value = 0;
    return result;
}

std::unique_ptr<BaseSquare> CommunitySquare::clone() const {
    return std::make_unique<CommunitySquare>(*this);
}