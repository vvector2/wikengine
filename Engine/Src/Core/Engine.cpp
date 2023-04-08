//
// Created by wiktor on 07.02.23.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "InputManager.h"
#include "ScriptComponent.h"

void Engine::Setup() {
    if (!glfwInit())
        throw std::runtime_error("Failed to init glfw lib");

    window = glfwCreateWindow(initWidth, initHeight, "Hello World", NULL, NULL);
    if (!window)
    {
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    imGuiDebugHelper = new ImGuiDebugHelper(window);
}

void Engine::Run(Scene& scene) {
    for(auto child: scene.GetChilds())
        SetupEntity(*child);

    while (!glfwWindowShouldClose(window))
    {
        if (InputManager::KeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        HandleDeltaTime();

        for(auto child: scene.GetChilds())
            UpdateEntity(*child);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.95, 0.95, 0.95, 1);

        if (imGuiDebugHelper != nullptr){
            imGuiDebugHelper->Render();
        }

        renderer.Render(scene);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Engine::~Engine() {
    if(window != nullptr)
        glfwDestroyWindow(window);
    glfwTerminate();
    delete imGuiDebugHelper;
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Engine::HandleDeltaTime() {
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

Engine::Engine(GLint _initWidth, GLint _initHeight): initWidth(_initWidth), initHeight(_initHeight) {
    deltaTime = 0;
    lastFrame = 0;
}

void Engine::SetupEntity(Entity &entity) {
    auto scriptComponent = entity.GetComponent<ScriptComponent>();
    if(scriptComponent != nullptr)
        scriptComponent->Setup();

    for(auto child: entity.GetChilds()){
        SetupEntity(*child);
    }
}

void Engine::UpdateEntity(Entity &entity) {
    auto scriptComponent = entity.GetComponent<ScriptComponent>();
    if(scriptComponent != nullptr)
        scriptComponent->Update(deltaTime);

    for(auto child: entity.GetChilds()){
        UpdateEntity(*child);
    }
}

