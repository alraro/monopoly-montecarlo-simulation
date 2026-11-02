#include "GenericViewComponents.hpp"
#include "Simulation.hpp"
#include "ConfigParser.hpp"

struct NullProgress : IProgressView {
    void updateProgress(uint64_t) override {}
    void initializeSimulationStart(uint64_t) override {}
    void setOnCancelCallback(std::function<void()>) override {}
    void setOnGoToConfigCallback(std::function<void()>) override {}
    void renderFrame() override {}
};

int main(int argc, char **argv) {
    auto config = ConfigParser::configFromCommandLine(argc, argv);
    NullProgress progress;
    Simulation simulation(config, progress);
    simulation.run();
}