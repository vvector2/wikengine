//
// Created by wiktor on 07.02.23.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "InputManager.h"
#include "ScriptComponent.h"

reactphysics3d::PhysicsCommon Engine::physicsCommon;
reactphysics3d::PhysicsWorld *Engine::physicsWorld;
reactphysics3d::DebugRenderer *Engine::debugRenderer;

void Engine::Setup() {
    if (!glfwInit())
        throw std::runtime_error("Failed to init glfw lib");

    window = glfwCreateWindow(initWidth, initHeight, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Failed to initialize GLEW\n");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    InputManager::Reset();
    glfwSetCursorPosCallback(window, InputManager::mouseCallback);
    glfwSetScrollCallback(window, InputManager::scrollCallback);
    glfwSetKeyCallback(window, InputManager::keyCallback);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    imGuiDebugHelper = new ImGuiDebugHelper(window);

    physicsWorld = Engine::physicsCommon.createPhysicsWorld();
    physicsWorld->setIsDebugRenderingEnabled(true);
    Engine::debugRenderer = &physicsWorld->getDebugRenderer();
    reactphysics3d::DefaultLogger *logger = physicsCommon.createDefaultLogger();
    reactphysics3d::PhysicsCommon::setLogger(logger);
    debugRenderer->setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
}

void Engine::Run(Scene &scene) {
    SetupEntities(scene);

    while (!glfwWindowShouldClose(window)) {
        PollEvents();

        UpdatePhysicsWorld();

        UpdateEntities(scene);

        Render(scene);
    }
}

Engine::~Engine() {
    if (window != nullptr)
        glfwDestroyWindow(window);
    glfwTerminate();
    delete imGuiDebugHelper;
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Engine::Engine(GLint _initWidth, GLint _initHeight) : initWidth(_initWidth), initHeight(_initHeight) {
    deltaTime = 0;
    lastFrame = 0;
}

void Engine::SetupEntity(Entity &entity) {
    auto scriptComponent = entity.GetComponent<ScriptComponent>(ScriptComponentType);
    if (scriptComponent != nullptr)
        scriptComponent->Setup();

    for (auto child: entity.GetChilds()) {
        SetupEntity(*child);
    }
}

void Engine::UpdateEntity(Entity &entity) {
//    auto rigidBodyComponent = entity.GetComponent<ScriptComponent>(ScriptComponentType);
//    auto tranform = entity.GetComponent<TransformComponent>(TransformComponentType);
//
//    decimal factor = accumulator / TimeStep;
//
//// Get the updated transform of the body
//    Transform currTransform = body->getTransform();
//
//// Compute the interpolated transform of the rigid body
//    Transform interpolatedTransform = Transform::interpolateTransforms(prevTransform, currTransform, factor);

    auto scriptComponent = entity.GetComponent<ScriptComponent>(ScriptComponentType);
    if (scriptComponent != nullptr)
        scriptComponent->Update(deltaTime);

    for (auto child: entity.GetChilds()) {
        UpdateEntity(*child);
    }
}

void Engine::UpdatePhysicsWorld() {
    auto currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    accumulator += deltaTime;

    while (accumulator >= TimeStep) {
        physicsWorld->update(static_cast<float>(TimeStep));
        accumulator -= TimeStep;
    }

}

void Engine::Render(Scene &scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.95, 0.95, 0.95, 1);

    renderer.Render(scene);
    if (imGuiDebugHelper != nullptr) {
        imGuiDebugHelper->Render();
    }

    glfwSwapBuffers(window);
}

void Engine::PollEvents() {
    glfwPollEvents();
    if (InputManager::KeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Engine::SetupEntities(Scene &scene) {
    for (auto child: scene.GetChilds())
        SetupEntity(*child);
}

void Engine::UpdateEntities(Scene &scene) {
    for (auto child: scene.GetChilds())
        UpdateEntity(*child);
}


