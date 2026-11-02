#pragma once

#include <string>
#include <monopoly/strategy/Strategy.hpp>
#include <memory>
#include <monopoly/extra/Types.hpp>

namespace monopoly {

struct PlayerInfo {
    PlayerId id;
    std::string name;
    // std::unique_ptr<Strategy> strategy; //TODO: Consider using function pointers or std::function.
};

}
