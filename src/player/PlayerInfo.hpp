#ifndef PLAYERINFO_HPP
# define PLAYERINFO_HPP
# include <string>
# include "Strategy.hpp"
# include <memory>

struct PlayerInfo {
    int id;
    std::string name;
    std::unique_ptr<Strategy> strategy; //TODO: Consider using function pointers or std::function.
};

#endif
