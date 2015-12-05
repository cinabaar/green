#pragma once

#include <nano_signal_slot.hpp>
#include <GLFW/glfw3.h>

class Input
{
public:
    struct KeyVariables
    {
        int key;
        int scancode;
        int action;
        int mods;
    };

    static Input& get()
    {
        static Input instance;
        return instance;
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    Nano::Signal<void(KeyVariables)> keyAction;
};


