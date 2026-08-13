#include "CommunitySquare.hpp"

CommunitySquare::CommunitySquare(): _name("Community"), _timesLandedOn(0) {}

CommunitySquare::CommunitySquare(const CommunitySquare &other): _name(other._name), _timesLandedOn(other._timesLandedOn) {}

CommunitySquare &CommunitySquare::operator=(const CommunitySquare &other) {
    if (this != &other) {
        _name = other._name;
        _timesLandedOn = other._timesLandedOn;
    }
    return *this;
}

CommunitySquare::~CommunitySquare() {}

EffectResult CommunitySquare::getSquareEffect(const Player &player) const {
    EffectResult result;
    result.type = EffectType::NONE;
    result.value = 0;
    return result;
}

BaseSquare *CommunitySquare::clone() const {
    return new CommunitySquare(*this);
}