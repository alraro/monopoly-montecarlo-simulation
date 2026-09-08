#pragma once
#include <cstdint>


using PlayerId  =   uint32_t;
using SquareId  =   uint32_t;
using GameId    =   uint32_t;
using Money     =   int64_t;
using StatCount =   uint32_t; // Counts of turns, landings, etc. should be non-negative and fit within 32 bits.

struct MonopolyDiceRollResult {
    uint8_t die1;
    uint8_t die2;
    constexpr uint8_t total() const noexcept { return die1 + die2; }
    constexpr bool areDoubles() const noexcept { return die1 == die2; }
};

struct PlayerStats {
    StatCount turnsSpentInJail{0};
    StatCount timesJailed{0};
    StatCount totalTurns{0};
    StatCount totalDiceRolls{0};
    StatCount totalDoublesRolled{0};
};
