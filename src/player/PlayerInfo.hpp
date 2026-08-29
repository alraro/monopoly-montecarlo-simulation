#pragma once

#include <string>
#include "Strategy.hpp"
#include <memory>
#include "Types.hpp"

struct PlayerInfo {
    PlayerId id;
    std::string name;
    // std::unique_ptr<Strategy> strategy; //TODO: Consider using function pointers or std::function.
};

