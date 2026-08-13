#ifndef COMMUNITYSQUARE_HPP
# define COMMUNITYSQUARE_HPP
# include "BaseSquare.hpp"

class CommunitySquare : public BaseSquare {
    protected:
        virtual EffectResult getSquareEffect(const Player &player) const;
    public:
        CommunitySquare();
        CommunitySquare(const CommunitySquare &other);
        CommunitySquare &operator=(const CommunitySquare &other);
        virtual ~CommunitySquare();

        virtual BaseSquare *clone() const;
};

#endif