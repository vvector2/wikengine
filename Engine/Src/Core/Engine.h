//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_ENGINE_H
#define WIKENGINE_ENGINE_H


#include "Scene.h"
#include "GLFW/glfw3.h"
#include "SimpleForwardRenderer.h"
#include "ImGuiDebugHelper.h"

class Engine {
public:
    Engine(GLint _initWidth, GLint _initHeight);

    void Setup();

    void Run(Scene &scene);

    ~Engine();

private:
    GLFWwindow *window = nullptr;
    ImGuiDebugHelper *imGuiDebugHelper = nullptr;
    GLint initWidth;
    GLint initHeight;
    float deltaTime;
    float lastFrame;
    SimpleForwardRenderer renderer;

    void HandleDeltaTime();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void SetupEntity(Entity &entity);

    void UpdateEntity(Entity &entity);
};


#endif //WIKENGINE_ENGINE_H
