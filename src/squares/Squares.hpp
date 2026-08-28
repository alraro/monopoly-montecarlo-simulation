#ifndef SQUARES_HPP
# define SQUARES_HPP
# include "effects.hpp"
# include "Player.hpp"
# include "SimulationRules.hpp"
# include <variant>

struct PropertySquare {
    int ownerId = -1;
    int housesBuilt = 0;
    bool hotelBuilt = false;
    bool isMortgaged = false;

    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        if (ownerId == -1 || ownerId == player.id || isMortgaged) {
            return {SquareEffectType::None, 0};
        } else {
            int rent = rules.squares[player.currentSquare].rent[hotelBuilt ? 5 : std::min(housesBuilt, 4)];
            return {SquareEffectType::Pay, rent};
        }
    }
};

struct CommunitySquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        return {SquareEffectType::None, 0}; //TODO: Implement community square effects
    }
};

struct GoToJailSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        return {SquareEffectType::GoToJail, 0};
    }
};

struct JailSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        return {SquareEffectType::None, 0};
    }
};

struct LuckSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        return {SquareEffectType::None, 0}; //TODO: Implement luck square effects
    }
};

struct ParkingSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        return {SquareEffectType::None, 0}; //TODO: Implement parking square effects
    }
};

struct StartSquare {
    SquareEffectResult getSquareEffect(const Player &player, const SimulationRules &rules) const {
        return {SquareEffectType::None, 0}; //TODO: Implement start square effects
    }
};

using Square = std::variant<PropertySquare, CommunitySquare, GoToJailSquare, JailSquare, LuckSquare, ParkingSquare, StartSquare>;


#endif