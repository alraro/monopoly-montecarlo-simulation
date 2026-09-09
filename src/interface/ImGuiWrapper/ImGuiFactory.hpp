#pragma once
#include "GenericViewComponents.hpp"
#include "ImGuiMainWindow.hpp"
#include "ImGuiConfigView.hpp"
#include "ImGuiProgressView.hpp"
#include <memory>

class ImGuiFactory : public IGUIFactory {
    public:
        std::unique_ptr<IMainWindow> createMainWindow() override {
            return std::make_unique<ImGuiMainWindow>();
        }
        std::unique_ptr<IConfigView> createConfigView() override {
            return std::make_unique<ImGuiConfigView>();
        };
        std::unique_ptr<IProgressView> createProgressView() override {
            return std::make_unique<ImGuiProgressView>();
        };
};