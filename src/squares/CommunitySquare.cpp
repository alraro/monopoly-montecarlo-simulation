#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): BaseSquare("Community") {}

EffectResult CommunitySquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}
