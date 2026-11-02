#pragma once

namespace monopoly {

enum class SquareEffectType {
    None,
    Move,
    GoToJail,
    Pay,
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

}