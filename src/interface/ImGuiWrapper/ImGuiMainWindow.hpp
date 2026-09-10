#pragma once
#include "GenericViewComponents.hpp"
#include <GLFW/glfw3.h>

class ImGuiMainWindow : public IMainWindow {
    private:
        GLFWwindow* _window;
        IView*      _currentView = nullptr;
        bool        _isWindowOpen;
    public:
        ImGuiMainWindow();
        ~ImGuiMainWindow();

        void setMainView(IView* displayView) override;
        bool openWindow(int width, int height, const std::string_view title) override;
        void closeWindow() override;
        void display() override;
};