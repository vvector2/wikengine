//
// Created by wiktor on 07.02.23.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "InputManager.h"

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
}

void Engine::Run(Scene scene) {
    while (!glfwWindowShouldClose(window))
    {
        HandleDeltaTime();
        renderer.Render(scene);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Engine::~Engine() {
    if(window != nullptr)
        glfwDestroyWindow(window);
    glfwTerminate();
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

