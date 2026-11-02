#pragma once

#include <string>
#include <array>

namespace monopoly {

enum class SquareType {
    Property,
    Community,
    GoToJail,
    Jail,
    Luck,
    Parking,
    Start
};

struct SquareInfo {
    std::string name;
    SquareType type;

    int buyPrice = 0;
    int housePrice = 0;
    int hotelPrice = 0;

    std::array<int, 6> rent = {0, 0, 0, 0, 0, 0};

    int effectValue = 0;
};

}
