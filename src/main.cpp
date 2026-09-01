#include "Logger.hpp"
#include "SimulationConfig.hpp"
#include "Simulation.hpp"
#include <functional>
#include <unordered_map>

namespace {

    using ArgHandler = std::function<void(SimulationConfig&, const std::function<std::string()>&)>;

    struct ArgSpec {
        std::vector<std::string> names;
        ArgHandler handler;
    };
    
    const std::vector<ArgSpec> kArgSpecs = {
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
            try {
                config.logLevel = Logger::getLogLevelFromName(level);
            } catch (const Logger::LogLevelNotFoundException &e) {
                Logger::error(e.what());
                exit(1);
            }
        }},
        {{"players-stats"}, [](SimulationConfig &config, const auto &nextArg) {
            config.playersStatisticsFilename = nextArg();
        }},
        {{"squares-stats"}, [](SimulationConfig &config, const auto &nextArg) {
            config.squaresStatisticsFilename = nextArg();
        }},
        {{"parallel", "p"}, [](SimulationConfig &config, const auto &) {
            config.runInParallel = true;
        }},
    };

    const std::unordered_map<std::string, ArgHandler> kArgHandlers = [] {
        std::unordered_map<std::string, ArgHandler> map;
        for (const auto &spec : kArgSpecs) {
            for (const auto &name : spec.names) {
                map.emplace(name, spec.handler);
            }
        }
        return map;
    }();

    void parseProgramFlags(SimulationConfig &config, int argc, char *argv[]) {
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
    }

    void setupPlayersAndSquaresInfo(SimulationConfig &config) {
        std::vector<PlayerInfo> players;
        
        players.emplace_back(0, "Player 1");
        players.emplace_back(1, "Player 2");

        std::vector<SquareInfo> squares;
        squares.emplace_back("Start", SquareType::Start);
        squares.emplace_back("Property 1", SquareType::Property);
        squares.emplace_back("Community Chest", SquareType::Community);
        squares.emplace_back("Property 2", SquareType::Property);
        squares.emplace_back("Go To Jail", SquareType::GoToJail);
        squares.emplace_back("Jail", SquareType::Jail);
        squares.emplace_back("Property 3", SquareType::Property);

        config.players = std::move(players);
        config.squares = std::move(squares);
    }

    SimulationConfig setupSimulationConfigs(int argc, char *argv[]) {
        SimulationConfig configs;
        Logger::debug("Setting up simulation parameters...");
    
        parseProgramFlags(configs, argc, argv);
        setupPlayersAndSquaresInfo(configs);
        
        return configs;
    }
}

int main(int argc, char *argv[]) {
    SimulationConfig configs = setupSimulationConfigs(argc, argv); 

    Logger::setLogLevel(configs.logLevel);
    Logger::info("Random seed: ", configs.seed);
    
    Simulation simulation(configs);

    simulation.run();
    return 0;
}