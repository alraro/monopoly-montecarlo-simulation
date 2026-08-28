#ifndef BASICSTRATEGY_HPP
# define BASICSTRATEGY_HPP
# include "Strategy.hpp"

class BasicStrategy : public Strategy {
    private:
        BasicStrategy() = default;
        ~BasicStrategy() override = default;
    public:
        static BasicStrategy& getInstance();

        BasicStrategy(const BasicStrategy&) = delete;
        BasicStrategy& operator=(const BasicStrategy&) = delete;
        BasicStrategy(BasicStrategy&&) = delete;
        BasicStrategy& operator=(BasicStrategy&&) = delete;

        PlayerStrategyActionResult      decidePlayerAction() const override;
        JailedPlayerStrategyActionType  decideJailedPlayerAction() const override;
        bool                            decideToBuyProperty() const override;
};

#endif