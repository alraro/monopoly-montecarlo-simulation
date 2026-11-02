#pragma once

#include <monopoly/interface/GenericViewComponents.hpp>
#include <monopoly/interface/imgui/ImGuiMainWindow.hpp>
#include <monopoly/interface/imgui/ImGuiConfigView.hpp>
#include <monopoly/interface/imgui/ImGuiProgressView.hpp>
#include <memory>

namespace monopoly {

class ImGuiFactory : public IGUIFactory {
    public:
        std::unique_ptr<IMainWindow> createMainWindow() override {
            return std::make_unique<ImGuiMainWindow>();
        }
        std::unique_ptr<IConfigView> createConfigView(SimulationConfig &config) override {
            return std::make_unique<ImGuiConfigView>(config);
        };
        std::unique_ptr<IProgressView> createProgressView() override {
            return std::make_unique<ImGuiProgressView>();
        };
};

}
