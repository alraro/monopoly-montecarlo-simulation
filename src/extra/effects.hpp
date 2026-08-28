#ifndef EFFECTS_HPP
# define EFFECTS_HPP

enum class SquareEffectType {
    None,
    Move,
    GoToJail,
};

struct SquareEffectResult {
    SquareEffectType type = SquareEffectType::None;
    int value = 0;
};

enum class PlayerStrategyActionType {
    DoNothing,
    BuildHouse,
    SellHouse,
    MortgageProperty,
    UnmortgageProperty,
};

struct PlayerStrategyActionResult {
    PlayerStrategyActionType type = PlayerStrategyActionType::DoNothing;
    int value = 0;
};

enum class JailedPlayerStrategyActionType {
    PayBail,
    RollDice,
    UseCard,
};

#endif