#pragma once
#include "GenericViewComponents.hpp"
#include "imgui.h"

class ImGuiProgressView : public IProgressView {
    private:
        float _progress = 0.0f;
        CancelCallback _onCancelCallback;
        GoToConfigCallback _onGoToConfigCallback;
        bool _showGoToConfigButton = false;
    public:
        void setupProgressBar(uint64_t totalGames) override {
            (void)totalGames;
            _progress = 0.0f;
        }

        void updateProgress(uint64_t completedCount, uint64_t totalGames) override {
            _progress = static_cast<float>(completedCount) / static_cast<float>(totalGames);
        }

        void renderFrame() override {
            ImGui::Begin("Ejecutando Simulación");
            ImGui::Text("Calculando Montecarlo...");
            ImGui::ProgressBar(_progress, ImVec2(-1.0f, 0.0f));
            if (_progress >= 1.0f) {
                _showGoToConfigButton = true;
                ImGui::Text("Simulación completada.");
                if (ImGui::Button("Volver atras") && _onGoToConfigCallback) {
                    _onGoToConfigCallback();
                }
            }
            if (ImGui::Button("Cancelar") && _onCancelCallback) {
                _showGoToConfigButton = true;
                _onCancelCallback();
                if (ImGui::Button("Volver atras") && _onGoToConfigCallback) {
                    _onGoToConfigCallback();
                }
            }
            ImGui::End();
        }

        void setOnCancelCallback(CancelCallback callback) override {
            _onCancelCallback = callback;
        }

        void setOnGoToConfigCallback(GoToConfigCallback callback) override {
            _onGoToConfigCallback = callback;
        }
};