#pragma once
#include "imgui.h"

class FullScreenWindow {
    public:
        FullScreenWindow(const char* title, ImGuiWindowFlags extraFlags = 0) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoSavedSettings
                | ImGuiWindowFlags_NoBringToFrontOnFocus
                | extraFlags;

            ImGui::Begin(title, nullptr, flags);
        }

        ~FullScreenWindow() {
            ImGui::PopStyleVar(2);
            ImGui::End();
        }

        FullScreenWindow(const FullScreenWindow&) = delete;
        FullScreenWindow& operator=(const FullScreenWindow&) = delete;
};