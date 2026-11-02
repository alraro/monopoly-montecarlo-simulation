#include <monopoly/interface/GenericViewComponents.hpp>
#include <monopoly/simulation/ConfigParser.hpp>
#include <monopoly/simulation/Simulation.hpp>

struct NullProgress : monopoly::IProgressView {
    void updateProgress(uint64_t) override {}
    void initializeSimulationStart(uint64_t) override {}
    void setOnCancelCallback(std::function<void()>) override {}
    void setOnGoToConfigCallback(std::function<void()>) override {}
    void renderFrame() override {}
};

int main(int argc, char **argv) {
    auto config = monopoly::ConfigParser::configFromCommandLine(argc, argv);
    NullProgress progress;
    monopoly::Simulation simulation(config, progress);
    simulation.run();
}
