//
// Created by wiktor on 23.04.24.
//

#include "Player.h"
#include "../TransformComponent.h"
#include "../InputManager.h"
#include "../Common.h"

void Player::Update(float deltaTime) {

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
//    if (firstMouse) {
//        lastX = InputManager::MouseX();
//        lastY = InputManager::MouseY();
//        firstMouse = false;
//    }
//
//    float xoffset = InputManager::MouseX() - lastX;
//    float yoffset = lastY - InputManager::MouseY();
//
//    lastX = InputManager::MouseX();
//    lastY = InputManager::MouseY();
//
//    cameraFirstPerson->ProcessMouseMovement(xoffset, yoffset);

    auto tranform = _entity->GetComponent<TransformComponent>(TransformComponentType);
    tranform->SetMatrix(cameraFirstPerson->GetViewMatrix());
}

void Player::Setup() {
    auto transform = _entity->GetComponent<TransformComponent>(TransformComponentType);
    auto mat = transform->WorldMatrix();
    auto baseY = glm::vec3(mat[0][1], mat[1][1], mat[2][1]);
    cameraFirstPerson = new CameraFirstPerson(glm::vec3(mat[3]), baseY);
}

Player::~Player() {
    delete cameraFirstPerson;
}
