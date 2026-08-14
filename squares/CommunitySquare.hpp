#ifndef COMMUNITYSQUARE_HPP
# define COMMUNITYSQUARE_HPP
# include "BaseSquare.hpp"

class CommunitySquare : public BaseSquare {
    protected:
        EffectResult getSquareEffect(const Player &player) const override;
    public:
        CommunitySquare();

        BaseSquare *clone() const override;
};

#endif