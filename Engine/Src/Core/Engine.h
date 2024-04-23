//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_ENGINE_H
#define WIKENGINE_ENGINE_H


#include "Scene.h"
#include "GLFW/glfw3.h"
#include "SimpleForwardRenderer.h"
#include "ImGuiDebugHelper.h"
#include <reactphysics3d/reactphysics3d.h>

class Engine {
public:
    Engine(GLint _initWidth, GLint _initHeight);

    void Setup();

    void Run(Scene &scene);

    ~Engine();

    static reactphysics3d::PhysicsCommon physicsCommon;
    static reactphysics3d::PhysicsWorld *physicsWorld;
    static reactphysics3d::DebugRenderer *debugRenderer;

private:
    GLFWwindow *window = nullptr;
    ImGuiDebugHelper *imGuiDebugHelper = nullptr;
    GLint initWidth;
    GLint initHeight;
    SimpleForwardRenderer renderer;
    const double TimeStep = 1.0 / 60.0;
    double accumulator = 0;
    double deltaTime;
    double lastFrame;

    void UpdatePhysicsWorld();

    void Render(Scene &scene);

    void PollEvents();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void SetupEntities(Scene &scene);

    void SetupEntity(Entity &entity);

    void UpdateEntities(Scene &scene);

    void UpdateEntity(Entity &entity);
};


#endif //WIKENGINE_ENGINE_H
