#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): BaseSquare("Community", 0) {}

CommunitySquare::CommunitySquare(const CommunitySquare &other): BaseSquare(other) {}

CommunitySquare &CommunitySquare::operator=(const CommunitySquare &other) {
    if (this != &other) {
        BaseSquare::operator=(other);
    }
    return *this;
}

CommunitySquare::~CommunitySquare() {}

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