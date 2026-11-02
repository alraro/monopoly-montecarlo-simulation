#include <monopoly/interface/imgui/ImGuiFactory.hpp>
#include <monopoly/MainController.hpp>

int main(int argc, char *argv[]) {
    monopoly::ImGuiFactory guiFactory;
    monopoly::MainController controller(guiFactory, argc, argv);
    controller.start();
    return 0;
}
