#pragma once
#include "GenericViewComponents.hpp"

class ImGuiMainWindow : public IMainWindow {
    public:
        void setMainView(IView* displayView) override {
            // TODO: Implement this method to set the main view of the ImGui main window.
        }

        void display() override {
            // TODO: Implement this method to display the ImGui main window.
        }
};