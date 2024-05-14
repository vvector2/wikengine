//
// Created by wiktor on 20.02.23.
//

#include <iostream>
#include "CameraFirstPersonScriptComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "ImGuiDebugHelper.h"
#include <glm/gtx/string_cast.hpp>

void CameraFirstPersonScriptComponent::Setup() {
    auto transform = _entity->GetComponent<TransformComponent>(TransformComponentType);
    auto mat = transform->Matrix();
    auto baseY = glm::vec3(mat[0][1], mat[1][1], mat[2][1]);
    std::cout << glm::to_string(baseY) << std::endl;
    cameraFirstPerson = new CameraFirstPerson(glm::vec3(mat[3]), baseY);
}

CameraFirstPersonScriptComponent::~CameraFirstPersonScriptComponent() {
    delete cameraFirstPerson;
}

void CameraFirstPersonScriptComponent::Update(float deltaTime) {
    auto dirArrow = glm::vec2(0, 0);

    if (InputManager::KeyState(GLFW_KEY_UP) != GLFW_RELEASE)
        dirArrow.y = 1;

    if (InputManager::KeyState(GLFW_KEY_DOWN) != GLFW_RELEASE)
        dirArrow.y = -1;

    if (InputManager::KeyState(GLFW_KEY_LEFT) != GLFW_RELEASE)
        dirArrow.x = -1;

    if (InputManager::KeyState(GLFW_KEY_RIGHT) != GLFW_RELEASE)
        dirArrow.x = 1;

    cameraFirstPerson->ProcessKeyboardArrow(dirArrow, deltaTime);

    auto dir = glm::vec2(0, 0);

    if (InputManager::KeyState(GLFW_KEY_W) != GLFW_RELEASE)
        dir.y = 1;

    if (InputManager::KeyState(GLFW_KEY_S) != GLFW_RELEASE)
        dir.y = -1;

    if (InputManager::KeyState(GLFW_KEY_A) != GLFW_RELEASE)
        dir.x = -1;

    if (InputManager::KeyState(GLFW_KEY_D) != GLFW_RELEASE)
        dir.x = 1;

    cameraFirstPerson->ProcessKeyboard(dir, deltaTime);
    cameraFirstPerson->ProcessMouseScroll(InputManager::ScrollY());

    if (firstMouse) {
        lastX = InputManager::MouseX();
        lastY = InputManager::MouseY();
        firstMouse = false;
    }

    float xoffset = InputManager::MouseX() - lastX;
    float yoffset = lastY - InputManager::MouseY();

    lastX = InputManager::MouseX();
    lastY = InputManager::MouseY();

    cameraFirstPerson->ProcessMouseMovement(xoffset, yoffset);

    auto tranform = _entity->GetComponent<TransformComponent>(TransformComponentType);
    auto viewMatrix = cameraFirstPerson->GetViewMatrix();
    tranform->SetMatrix(glm::mat4(viewMatrix[0], viewMatrix[1], viewMatrix[2], -viewMatrix[3]));

    ImGuiDebugHelper::renderDebugData.activeCamePosition = glm::vec3(cameraFirstPerson->Pos().x,
                                                                     cameraFirstPerson->Pos().y,
                                                                     cameraFirstPerson->Pos().z);
}

CameraFirstPersonScriptComponent::CameraFirstPersonScriptComponent() {
}
