#pragma once

#include "SimulationConfig.hpp"

namespace ConfigParser {
    SimulationConfig configFromCommandLine(int argc, char* argv[]);
}