#ifndef SQUARES_HPP
# define SQUARES_HPP
# include "effects.hpp"
# include "Player.hpp"
# include "SimulationConfig.hpp"
# include <variant>
# include <optional>

struct PropertySquare {
    std::optional<unsigned int> ownerId{std::nullopt};
    unsigned int housesBuilt = 0;
    bool hotelBuilt = false;
    bool isMortgaged = false;

    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        if (!ownerId.has_value() || ownerId == player.id || isMortgaged) {
            return {SquareEffectType::None, 0};
        } else {
            int rent = rules.squares[player.currentSquare].rent[hotelBuilt ? 5 : std::min(housesBuilt, 4u)];
            return {SquareEffectType::Pay, rent};
        }
    }
};

struct CommunitySquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        (void)player; // Unused parameter
        (void)rules;  // Unused parameter
        return {SquareEffectType::None, 0}; //TODO: Implement community square effects
    }
};

struct GoToJailSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        (void)player; // Unused parameter
        (void)rules;  // Unused parameter
        return {SquareEffectType::GoToJail, 0};
    }
};

struct JailSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        (void)player; // Unused parameter
        (void)rules;  // Unused parameter
        return {SquareEffectType::None, 0};
    }
};

struct LuckSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        (void)player; // Unused parameter
        (void)rules;  // Unused parameter
        return {SquareEffectType::None, 0}; //TODO: Implement luck square effects
    }
};

struct ParkingSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        (void)player; // Unused parameter
        (void)rules;  // Unused parameter
        return {SquareEffectType::None, 0}; //TODO: Implement parking square effects
    }
};

struct StartSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationConfig &rules) const {
        (void)player; // Unused parameter
        (void)rules;  // Unused parameter
        return {SquareEffectType::None, 0}; //TODO: Implement start square effects
    }
};

using Square = std::variant<
    PropertySquare,
    CommunitySquare,
    GoToJailSquare,
    JailSquare,
    LuckSquare,
    ParkingSquare,
    StartSquare
>;

inline SquareEffectResult getSquareEffect(const Square &square, const Player &player, const SimulationConfig &rules) {
    return std::visit([&](const auto& sq) {
        return sq.getSquareEffect(player, rules);
    }, square);
}


#endif