#include "SimulationConfig.hpp"
#include <functional>
#include "ConfigParser.hpp"

namespace ConfigParser {

    namespace {
        using ArgHandler = std::function<void(SimulationConfig&, const std::function<std::string()>&)>;
        
        struct ArgSpec {
            std::vector<std::string> names;
            ConfigParser::ArgHandler handler;
        };
        
        const std::vector<ConfigParser::ArgSpec> kArgSpecs = {
            {{"turns", "t"}, [](SimulationConfig &config, const auto &nextArg) {
                config.turnLimit = std::stoull(nextArg());
            }},
            {{"seed", "s"}, [](SimulationConfig &config, const auto &nextArg) {
                config.seed = std::stoull(nextArg());
            }},
            {{"games", "g"}, [](SimulationConfig &config, const auto &nextArg) {
                config.gameCount = std::stoull(nextArg());
                if (config.gameCount == 0) {
                    Logger::error("Game count must be greater than 0");
                    exit(1);
                }
            }},
            {{"threads"}, [](SimulationConfig &config, const auto &nextArg) {
                config.numThreads = static_cast<uint16_t>(std::stoul(nextArg()));
                if (config.numThreads == 0) {
                    Logger::error("Number of threads must be greater than 0");
                    exit(1);
                }
            }},
            {{"log-level", "l"}, [](SimulationConfig &config, const auto &nextArg) {
                std::string level = nextArg();
                auto parsedLevel = Logger::getLogLevelFromName(level);
                if (!parsedLevel) {
                    Logger::error("Unknown log level: ", level, ". <none|info|progress|error|debug>");
                    exit(1);
                }
                config.logLevel = *parsedLevel;
            }},
            {{"sim-name"}, [](SimulationConfig &config, const auto &nextArg) {
                config.simulationName = nextArg();
            }},
            {{"base-dir"}, [](SimulationConfig &config, const auto &nextArg) {
                config.baseDir = nextArg();
            }},
            {{"no-export-stats"}, [](SimulationConfig &config, const auto &) {
                config.exportStatistics = false;
            }},
            {{"parallel", "p"}, [](SimulationConfig &config, const auto &) {
                config.runInParallel = true;
            }},
            {{"no-interface"}, [](SimulationConfig &config, const auto &) {
                config.hasInterface = false;
            }}
        };
        
        const std::unordered_map<std::string, ArgHandler> kArgHandlers = [] {
            std::unordered_map<std::string, ArgHandler> map;
            for (const auto &spec : ConfigParser::kArgSpecs) {
                for (const auto &name : spec.names) {
                    map.emplace(name, spec.handler);
                }
            }
            return map;
        }();
    }
    
    SimulationConfig configFromCommandLine(int argc, char *argv[]) {
        SimulationConfig config;
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
    
            if (arg.starts_with("--")) {
                arg = arg.substr(2);
            } else if (arg.starts_with("-")) {
                arg = arg.substr(1);
            } else {
                Logger::error("Unknown argument: ", arg);
                exit(1);
            }
    
            if (arg == "help" || arg == "h") {
                Logger::log("Usage: ", argv[0], " [--turns <number_of_turns>] [--seed <random_seed>] [--log-level <none|info|error|debug>] [--help | -h]");
                exit(0);
            }
    
            auto it = kArgHandlers.find(arg);
            if (it == kArgHandlers.end()) {
                Logger::error("Unknown argument: ", arg, ".\nCheck ", argv[0], " --help for usage.");
                exit(1);
            }
    
            auto nextArg = [&]() -> std::string {
                if (i + 1 >= argc) {
                    Logger::error("Missing value for argument: ", arg);
                    exit(1);
                }
                return argv[++i];
            };
    
            it->second(config, nextArg);
        }
        return config;
    }

}
