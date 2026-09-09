#pragma once
#include "GenericViewComponents.hpp"

class ImGuiFactory : public IGUIFactory {
    public:
        std::unique_ptr<IMainWindow> createMainWindow() override {
            return nullptr; // TODO: Implement this method to create and return an instance of your ImGui-based main window.
        }
        std::unique_ptr<IConfigView> createConfigView() override {
            return nullptr; // TODO: Implement this method to create and return an instance of your ImGui-based config view.
        };
        std::unique_ptr<IProgressView> createProgressView() override {
            return nullptr; // TODO: Implement this method to create and return an instance of your ImGui-based progress view.
        };
};