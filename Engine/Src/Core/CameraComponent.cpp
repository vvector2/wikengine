//
// Created by wiktor on 14.02.23.
//

#include "CameraComponent.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Entity.h"
#include "TransformComponent.h"


CameraComponent::CameraComponent(float foe, float ratio, float near, float far) {
    projection = glm::perspective(foe, ratio, near, far);
}

CameraComponent::CameraComponent(float left, float right, float up, float bottom, float near, float far) {
    projection = glm::ortho(left, right, bottom, up, near, far);
}

glm::mat4 CameraComponent::View() {
    auto transform = _entity->GetComponent<TransformComponent>(TransformComponentType);
    auto worldMatrix = transform->WorldMatrix();
    glm::mat4 view(worldMatrix[0], worldMatrix[1], worldMatrix[2], glm::vec4(-glm::vec3(worldMatrix[3]), 1));
    return view;
}
