#ifndef COMMUNITYSQUARE_HPP
# define COMMUNITYSQUARE_HPP
# include "BaseSquare.hpp"

class CommunitySquare : public BaseSquare {
    public:
        CommunitySquare();
        
        EffectResult getSquareEffect(const Player &player) const override;
        virtual std::unique_ptr<BaseSquare> clone() const override;
};

#endif