//
// Created by wiktor on 09.02.23.
//

#ifndef WIKENGINE_INPUTMANAGER_H
#define WIKENGINE_INPUTMANAGER_H
#define INPUT_MANAGER_KEY_SIZE_RANGE 350


#include <array>
#include "GLFW/glfw3.h"


class InputManager {
public:
    static void mouseCallback(GLFWwindow *window, double xposIn, double yposIn);

    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void Reset();

    static float MouseX() { return mouseX; }

    static float MouseY() { return mouseY; }

    static float ScrollY() { return scrollY; }

    static int KeyState(int key) { return keys[key]; }

    static int FirstMouse() { return firstMouse; }

private:
    static bool firstMouse;
    static float mouseX;
    static float mouseY;
    static float scrollY;
    static std::array<int, INPUT_MANAGER_KEY_SIZE_RANGE> keys;
};


#endif //WIKENGINE_INPUTMANAGER_H
