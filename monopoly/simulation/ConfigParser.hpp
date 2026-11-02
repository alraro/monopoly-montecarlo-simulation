#pragma once

#include <monopoly/simulation/SimulationConfig.hpp>

namespace monopoly {

namespace ConfigParser {
    SimulationConfig configFromCommandLine(int argc, char* argv[]);
}

}
