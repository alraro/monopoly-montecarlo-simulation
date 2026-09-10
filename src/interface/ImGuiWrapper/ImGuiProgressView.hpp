#pragma once
#include "GenericViewComponents.hpp"
#include "imgui.h"

class ImGuiProgressView : public IProgressView {
    private:
        float _progress = 0.0f;
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
            ImGui::End();
        }
};