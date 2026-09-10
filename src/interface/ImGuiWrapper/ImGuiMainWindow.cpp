#include "ImGuiMainWindow.hpp"
#include "Logger.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ImGuiMainWindow::ImGuiMainWindow() {
    if (!glfwInit()) {
        Logger::error("Couldn't load graphical interface. Exiting");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    _window = glfwCreateWindow(1280, 720, "Monopoly Simulator", nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

ImGuiMainWindow::~ImGuiMainWindow() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(_window);
    glfwTerminate();
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
