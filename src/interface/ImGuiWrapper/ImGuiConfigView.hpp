#pragma once
#include "GenericViewComponents.hpp"
#include "imgui.h"
#include <vector>

class ImGuiConfigView : public IConfigView {
    private:
        SimulationConfig _config;
        RunCallback _runCallback;
    public:
        ImGuiConfigView(SimulationConfig& config) : _config(config) {};
        void setOnRunCallback(RunCallback callback) override {
            _runCallback = callback;
        }

        void renderFrame() override {
            ImGui::Begin("Simulation Configuration");

            ImGui::InputScalar("Game count", ImGuiDataType_U64, &_config.gameCount);
            ImGui::InputScalar("Max turns per game", ImGuiDataType_U64, &_config.turnLimit);

            ImGui::Checkbox("Run in parallel", &_config.runInParallel);
            ImGui::Checkbox("Export statistics to CSV", &_config.exportStatistics);
            
            ImGui::Separator();

            if (ImGui::Button("Run Simulation")) {
                if (_runCallback) {

                    // Temporary hardcoded players for demonstration purposes
                    std::vector<PlayerInfo> players = {
                        {0, "Player 1"},
                        {1, "Player 2"}
                    };
                    _config.players = players;

                    // Temporary hardcoded squares for demonstration purposes
                    std::vector<SquareInfo> squares;
                    squares.emplace_back("Square 1", SquareType::Property);
                    squares.emplace_back("Square 2", SquareType::Property);
                    squares.emplace_back("Square 3", SquareType::Property);
                    squares.emplace_back("Square 4", SquareType::Property);
                    squares.emplace_back("Square 5", SquareType::Property);
                    squares.emplace_back("Square 6", SquareType::Property);
                    squares.emplace_back("Square 7", SquareType::Property);
                    squares.emplace_back("Square 8", SquareType::Property);
                    _config.squares = squares;

                    _runCallback(_config);
                }
            }


            ImGui::End();
        }
};