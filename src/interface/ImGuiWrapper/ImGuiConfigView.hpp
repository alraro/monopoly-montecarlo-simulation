#pragma once
#include "GenericViewComponents.hpp"
#include "Logger.hpp"
#include "imgui.h"
#include <vector>

class ImGuiConfigView : public IConfigView {
    private:
        constexpr static size_t BASEDIRBUFFERSIZE = 200;
        constexpr static size_t SIMULATIONNAMEBUFFERSIZE = 200;
        SimulationConfig   &_config;
        RunCallback         _runCallback;
        int                 _selectedLogLevelIndex = 0;
        char                _baseDirBuffer[BASEDIRBUFFERSIZE] = {0};
        char                _simulationNameBuffer[SIMULATIONNAMEBUFFERSIZE] = {0};
    public:
        ImGuiConfigView(SimulationConfig& config) : _config(config) {};
        void setOnRunCallback(RunCallback callback) override {
            _runCallback = callback;
        }

        void renderFrame() override {
            ImGui::Begin("Simulation Configuration");

            ImGui::InputScalar("Max turns per game", ImGuiDataType_U64, &_config.turnLimit);
            ImGui::InputScalar("Random seed", ImGuiDataType_U64, &_config.seed);
            ImGui::InputScalar("Game count", ImGuiDataType_U64, &_config.gameCount);
            ImGui::InputScalar("Number of threads", ImGuiDataType_U32, &_config.numThreads);

            ImGui::InputText("Base Directory", _baseDirBuffer, BASEDIRBUFFERSIZE);
            ImGui::InputText("Simulation Name", _simulationNameBuffer, SIMULATIONNAMEBUFFERSIZE);

            if (ImGui::Combo("Log Level", &_selectedLogLevelIndex, Logger::logLevelStrings, Logger::LOG_LEVEL_COUNT)) {
                _config.logLevel = Logger::getLogLevelFromName(Logger::logLevelStrings[_selectedLogLevelIndex]).value_or(LogLevel::Info);
            }

            ImGui::Checkbox("Run in parallel", &_config.runInParallel);
            ImGui::Checkbox("Export statistics to CSV", &_config.exportStatistics);
            
            ImGui::Separator();

            if (ImGui::Button("Run Simulation")) {
                if (_runCallback) {

                    if (_baseDirBuffer[0] != '\0') {
                        _config.baseDir = std::string(_baseDirBuffer);
                    }
                    
                    if (_simulationNameBuffer[0] != '\0') {
                        _config.simulationName = std::string(_simulationNameBuffer);
                    }

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