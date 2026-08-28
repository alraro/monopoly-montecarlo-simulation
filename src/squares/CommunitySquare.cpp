#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): BaseSquare("Community") {}

SquareEffectResult CommunitySquare::getSquareEffect(const Player &) const {
    return {SquareEffectType::None, 0};
}

std::unique_ptr<BaseSquare> CommunitySquare::clone() const {
    return std::make_unique<CommunitySquare>(*this);
}
