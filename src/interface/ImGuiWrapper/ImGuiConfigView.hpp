#pragma once
#include "GenericViewComponents.hpp"

class ImGuiConfigView : public IConfigView {
    private:
        RunCallback _runCallback;
    public:
        void setOnRunCallback(RunCallback callback) override {
            _runCallback = callback;
        }

        void renderFrame() override {
            // TODO: Implement this method to render the ImGui config view frame and handle user interactions.
        }
};