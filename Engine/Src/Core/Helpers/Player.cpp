//
// Created by wiktor on 23.04.24.
//

#include "Player.h"
#include "../TransformComponent.h"
#include "../InputManager.h"
#include "../Common.h"
#include "../CameraComponent.h"
#include "../RigidbodyComponent.h"

void Player::Update(float deltaTime) {
    auto rigidBody = _entity->GetComponent<RigidbodyComponent>(RigidbodyComponentType);
    auto transform = cameraEntity->GetComponent<TransformComponent>(TransformComponentType);
    auto playerMatrix = transform->WorldMatrix();

    auto dir = glm::vec2(0, 0);

    if (InputManager::KeyState(GLFW_KEY_I) != GLFW_RELEASE)
        dir.y = 1;

    if (InputManager::KeyState(GLFW_KEY_K) != GLFW_RELEASE)
        dir.y = -1;

    if (InputManager::KeyState(GLFW_KEY_J) != GLFW_RELEASE)
        dir.x = -1;

    if (InputManager::KeyState(GLFW_KEY_L) != GLFW_RELEASE)
        dir.x = 1;

    auto zBase = glm::vec3(0, 0, 1);
    auto xBase = glm::vec3(1, 0, 0);
    auto force = glm::vec3((xBase * dir.x + zBase * dir.y) * PLAYER_MOVEMENT_SPEED * deltaTime);


    rigidBody->GetRigidBody()->applyLocalForceAtCenterOfMass({force.x, force.y, force.z});
//
//    auto dirArrow = glm::vec2(0, 0);
//
//    if (InputManager::KeyState(GLFW_KEY_UP) != GLFW_RELEASE)
//        dirArrow.y = 1;
//
//    if (InputManager::KeyState(GLFW_KEY_DOWN) != GLFW_RELEASE)
//        dirArrow.y = -1;
//
//    if (InputManager::KeyState(GLFW_KEY_LEFT) != GLFW_RELEASE)
//        dirArrow.x = -1;
//
//    if (InputManager::KeyState(GLFW_KEY_RIGHT) != GLFW_RELEASE)
//        dirArrow.x = 1;
//
//    cameraFirstPerson->ProcessKeyboardArrow(dirArrow, deltaTime);

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

    //transform->SetMatrix(cameraFirstPerson->GetViewMatrix());
}

void Player::Setup() {
    auto transform = cameraEntity->GetComponent<TransformComponent>(TransformComponentType);
    auto mat = transform->Matrix();
    auto baseY = glm::vec3(mat[0][1], mat[1][1], mat[2][1]);
    cameraFirstPerson = new CameraFirstPerson(glm::vec3(mat[3]), baseY);
}

Player::~Player() {
    delete cameraFirstPerson;
}

void Player::SetCameraEntity(Entity *entity) {
    cameraEntity = entity;
}
