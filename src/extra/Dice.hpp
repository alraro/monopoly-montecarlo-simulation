#ifndef DICE_HPP
# define DICE_HPP
# include "Types.hpp"
# include <cstdint>
# include <random>

class Dice {
    private:
        std::mt19937 _generator;
        std::uniform_int_distribution<int> _dieDistribution{1, 6};
    public:
        Dice() : _generator(std::random_device{}()) {}
        Dice(uint64_t seed) : _generator(seed) {}

        void seed(uint64_t seed) {
            _generator.seed(seed);
        }

        MonopolyDiceRollResult rollMonopolyDice() {
            return {static_cast<uint8_t>(_dieDistribution(_generator)),
                    static_cast<uint8_t>(_dieDistribution(_generator))};
        }
        
};

#endif