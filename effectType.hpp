#ifndef EFFECTTYPE_HPP
# define EFFECTTYPE_HPP

enum EffectType {
    NONE,
    MOVE,
    GO_TO_JAIL,
};

struct EffectResult {
    EffectType type;
    int value;
};

#endif