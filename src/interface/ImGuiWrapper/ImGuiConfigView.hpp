#pragma once
#include "GenericViewComponents.hpp"

class ImGuiConfigView : public IConfigView {
    private:
        RunCallback _runCallback;
    public:
        void setOnRunCallback(RunCallback callback) override {
            _runCallback = callback;
        }
};