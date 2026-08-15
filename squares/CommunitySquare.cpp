#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): BaseSquare("Community") {}

EffectResult CommunitySquare::getSquareEffect(const Player &) const {
    return {EffectType::None, 0};
}

std::unique_ptr<BaseSquare> CommunitySquare::clone() const {
    return std::make_unique<CommunitySquare>(*this);
}