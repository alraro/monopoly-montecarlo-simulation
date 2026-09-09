#pragma once
#include "GenericViewComponents.hpp"

class ImGuiProgressView : public IProgressView {
    public:
        void setupProgressBar(uint64_t totalGames) override {
            (void)totalGames; // Avoid unused parameter warning
            // TODO: Implement this method to set up the progress bar with the total number of games in the ImGui progress view.
        }

        void updateProgress(uint64_t completedCount, uint64_t totalGames) override {
            (void)completedCount; // Avoid unused parameter warning
            (void)totalGames; // Avoid unused parameter warning
            // TODO: Implement this method to update the progress bar with the completed and total number of games in the ImGui progress view.
        }

        void renderFrame() override {
            // TODO: Implement this method to render the ImGui progress view frame and handle user interactions.
        }
};