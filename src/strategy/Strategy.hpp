#ifndef STRATEGY_HPP
# define STRATEGY_HPP
# include "effects.hpp"

class Strategy {
    public:
        Strategy() = default;
        virtual ~Strategy() = default;

        Strategy(const Strategy&) = delete;
        Strategy& operator=(const Strategy&) = delete;
        Strategy(Strategy&&) noexcept = delete;
        Strategy& operator=(Strategy&&) noexcept = delete;

        virtual PlayerStrategyActionResult      decidePlayerAction() const = 0;
        virtual JailedPlayerStrategyActionType  decideJailedPlayerAction() const = 0;
        virtual bool                            decideToBuyProperty() const = 0;
        
};

#endif