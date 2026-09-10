#include "SimulationConfig.hpp"
#include "ConfigParser.hpp"
#include "ImGuiFactory.hpp"
#include "MainController.hpp"

namespace {

    void setupDefaultPlayersAndSquaresInfo(SimulationConfig &config) {
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

}

int main(int argc, char *argv[]) {
    SimulationConfig configs = ConfigParser::configFromCommandLine(argc, argv); 

    setupDefaultPlayersAndSquaresInfo(configs);

    // Logger::setLogLevel(configs.logLevel);
    // Logger::info("Random seed: ", configs.seed);
    
    // if (!configs.isValid())
    //     return 1;

    // IProgressView* progressView = nullptr; 
    // Simulation simulation(configs, *progressView);
    // simulation.run();

    ImGuiFactory guiFactory;
    MainController controller(guiFactory);
    controller.start();

    return 0;
}