#include "ImGuiFactory.hpp"
#include "MainController.hpp"

int main(int argc, char *argv[]) {
    ImGuiFactory guiFactory;
    MainController controller(guiFactory, argc, argv);
    controller.start();
    return 0;
}