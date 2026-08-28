#include "BasicStrategy.hpp"

BasicStrategy& BasicStrategy::getInstance() {
    static BasicStrategy instance;
    return instance;
}

PlayerStrategyActionResult BasicStrategy::decidePlayerAction() const {
    PlayerStrategyActionResult result;
    result.type = PlayerStrategyActionType::DoNothing;
    return result;
}

JailedPlayerStrategyActionType BasicStrategy::decideJailedPlayerAction() const {
    return JailedPlayerStrategyActionType::RollDice;
}

bool BasicStrategy::decideToBuyProperty() const {
    return false;
}
