#include "Input.hpp"

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    KeyVariables var;
    var.action = action;
    var.key = key;
    var.mods = mods;
    var.scancode = scancode;

    get().keyAction.emit(std::move(var));
}
