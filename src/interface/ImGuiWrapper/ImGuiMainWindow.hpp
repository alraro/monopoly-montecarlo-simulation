#pragma once
#include "GenericViewComponents.hpp"
#include <GLFW/glfw3.h>

class ImGuiMainWindow : public IMainWindow {
    private:
        GLFWwindow* _window;
        IView*      _currentView = nullptr;
    public:
        ImGuiMainWindow();
        ~ImGuiMainWindow();

        void setMainView(IView* displayView) override;
        void display() override;
};