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
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void Reset();
private:
    static double mouseX;
    static double mouseY;
    static double scrollY;
    static std::array<int, INPUT_MANAGER_KEY_SIZE_RANGE> keys;
};


#endif //WIKENGINE_INPUTMANAGER_H
