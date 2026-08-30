#include "Game.hpp"
#include "Logger.hpp"
#include "simulationParams.hpp"
#include "Simulation.hpp"

namespace {
    void setupSimulationParams(SimulationConfig &params, int argc, char *argv[]) {
        Logger::debug("Setting up simulation parameters...");

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

            if (arg == "turns" && i + 1 < argc) {
                params.turns = std::stoull(argv[++i]);
            } else if (arg == "seed" && i + 1 < argc) {
                params.seed = std::stoull(argv[++i]);
            } else if (arg == "log-level" && i + 1 < argc) {
                std::string level = argv[++i];
                if (level == "none") {
                    params.logLevel = LogLevel::None;
                } else if (level == "progress") {
                    params.logLevel = LogLevel::Progress;
                } else if (level == "info") {
                    params.logLevel = LogLevel::Info;
                } else if (level == "error") {
                    params.logLevel = LogLevel::Error;
                } else if (level == "debug") {
                    params.logLevel = LogLevel::Debug;
                } else {
                    Logger::error("Unknown log level: ", level, " <none|info|error|debug>");
                    exit(1);
                }
            } else if (arg == "players-stats" && i + 1 < argc) {
                params.playersStatisticsFilename = argv[++i];
            } else if (arg == "squares-stats" && i + 1 < argc) {
                params.squaresStatisticsFilename = argv[++i];
            } else if (arg == "help" || arg == "h") {
                Logger::log("Usage: ", argv[0], " [--turns <number_of_turns>] [--seed <random_seed>] [--log-level <none|info|error|debug>] [--help | -h]");
                exit(0);
            } else if (arg == "parallel") {
                params.runInParallel = true;
            } else {
                Logger::error("Unknown argument: ", arg, ".\nCheck ", argv[0], " --help for usage.");
                exit(1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    SimulationConfig params;
    setupSimulationParams(params, argc, argv);

    Logger::setLogLevel(params.logLevel);
    Logger::info("Random seed: ", params.seed);
    
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
    
    Simulation simulation(squares, players);

    if (params.runInParallel) {
        simulation.runParallelMontecarloSimulation(120);
    } else {
        simulation.runSequentialMontecarloSimulation(120);
    }

    return 0;
}