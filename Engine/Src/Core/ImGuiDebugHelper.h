//
// Created by wiktor on 28.03.23.
//

#ifndef WIKENGINE_IMGUIDEBUGHELPER_H
#define WIKENGINE_IMGUIDEBUGHELPER_H


#include "GLFW/glfw3.h"
#include "imgui.h"
#include "glm/vec3.hpp"

struct RenderDebugData {
    glm::vec3 activeCamePosition;
};

class ImGuiDebugHelper {
public:
    explicit ImGuiDebugHelper(GLFWwindow *window);

    ~ImGuiDebugHelper();

    void Render();

    static RenderDebugData renderDebugData;
private:
    ImGuiIO *io;
};

#endif //WIKENGINE_IMGUIDEBUGHELPER_H
