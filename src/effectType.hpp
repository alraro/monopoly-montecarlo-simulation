#ifndef EFFECTTYPE_HPP
# define EFFECTTYPE_HPP

enum class EffectType {
    None,
    Move,
    GoToJail,
};

struct EffectResult {
    EffectType type = EffectType::None;
    int value = 0;
};

#endif