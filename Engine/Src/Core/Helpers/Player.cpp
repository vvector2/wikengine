//
// Created by wiktor on 23.04.24.
//

#include "Player.h"
#include "../TransformComponent.h"
#include "../InputManager.h"
#include "../CameraComponent.h"
#include "../RigidbodyComponent.h"

void Player::Update(float deltaTime) {
    auto transform = cameraEntity->GetComponent<TransformComponent>(TransformComponentType);

    HandleMovement(deltaTime);

    HandleCamera(deltaTime);

    auto viewMatrix = cameraFirstPerson->GetViewMatrix();
    transform->SetMatrix(glm::mat4(viewMatrix[0], viewMatrix[1], viewMatrix[2], -viewMatrix[3]));
}

void Player::Setup() {
    auto transform = cameraEntity->GetComponent<TransformComponent>(TransformComponentType);
    auto mat = transform->Matrix();
    auto baseY = glm::vec3(mat[0][1], mat[1][1], mat[2][1]);
    cameraFirstPerson = new CameraFirstPerson(glm::vec3(mat[3]), baseY);

    auto rigidBodyComponent = _entity->GetComponent<RigidbodyComponent>(RigidbodyComponentType);

    rigidBodyComponent->GetRigidBody()->setAngularLockAxisFactor({0, 1, 0});
    rigidBodyComponent->GetRigidBody()->getCollider(0)->getMaterial().setBounciness(0);
    //irigidBodyComponent->GetRigidBody()->getCollider(0)->getMaterial().setFrictionCoefficient(20);
}

Player::~Player() {
    delete cameraFirstPerson;
}

void Player::SetCameraEntity(Entity *entity) {
    cameraEntity = entity;
}

void Player::HandleMovement(float deltaTime) {
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

    auto front = glm::normalize(glm::vec3(playerMatrix[2]));
    auto xBase = glm::normalize(glm::vec3(playerMatrix[0]));

    auto force = (front * dir.y + xBase * dir.x) * PLAYER_MOVEMENT_SPEED_FORCE * deltaTime;

    rigidBody->GetRigidBody()->applyLocalForceAtCenterOfMass({force.x, 0, force.z});

    auto velocity = rigidBody->GetRigidBody()->getLinearVelocity();
    auto velocityV = glm::vec3(velocity.x, velocity.y, velocity.z);

    auto velocityV2D = glm::vec3(velocity.x, 0, velocity.z);
    auto velocityScalar = glm::length(velocityV2D);

    std::cout << "speed: " << velocityScalar << std::endl;
    if (MAX_SPEED < velocityScalar) {
        std::cout << "max speed reacted" << std::endl;
        auto adjustedVelocity = glm::normalize(velocityV) * MAX_SPEED;
        adjustedVelocity.y = velocityV.y;
        rigidBody->GetRigidBody()->setLinearVelocity({adjustedVelocity.x, adjustedVelocity.y, adjustedVelocity.z});
    }

}

void Player::HandleCamera(float deltaTime) {
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
}
