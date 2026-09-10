#include "ImGuiMainWindow.hpp"
#include "Logger.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ImGuiMainWindow::ImGuiMainWindow(): _window(nullptr), _isWindowOpen(false) {}

ImGuiMainWindow::~ImGuiMainWindow() {
    this->closeWindow();
}

bool ImGuiMainWindow::openWindow(int width, int height, const std::string_view title) {
    if (_isWindowOpen) {
        return true; 
    }

    if (!glfwInit()) {
        Logger::error("Couldn't load graphical interface. glfwInit failed.");
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    _window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!_window) {
        Logger::error("Failed to create GLFW window.");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    _isWindowOpen = true;
    return true;
}

void ImGuiMainWindow::closeWindow() {
    if (!_isWindowOpen) return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (_window) {
        glfwDestroyWindow(_window);
        _window = nullptr;
    }
    glfwTerminate();

    _isWindowOpen = false;
}

void ImGuiMainWindow::setMainView(IView* displayView) {
    _currentView = displayView;
}

void ImGuiMainWindow::display() {
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (_currentView) {
            _currentView->renderFrame();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(_window);
    }
}
