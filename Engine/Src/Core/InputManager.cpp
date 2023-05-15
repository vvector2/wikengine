//
// Created by wiktor on 09.02.23.
//

#include "InputManager.h"

void InputManager::mouseCallback(GLFWwindow *window, double xposIn, double yposIn) {
    mouseX = xposIn;
    mouseY = yposIn;
}

void InputManager::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    scrollY = yoffset;
}

void InputManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == -1)
        return;
    keys[key] = action;
}

void InputManager::Reset() {
    mouseX = 0;
    mouseY = 0;
    scrollY = 0;
    for (int i = 0; i < INPUT_MANAGER_KEY_SIZE_RANGE; i++)
        keys[i] = GLFW_RELEASE;

}

float InputManager::mouseX;
float InputManager::mouseY;
float InputManager::scrollY;
std::array<int, INPUT_MANAGER_KEY_SIZE_RANGE> InputManager::keys;

