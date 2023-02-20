//
// Created by wiktor on 14.02.23.
//

#include "CameraComponent.h"
#include "glm/gtc/matrix_transform.hpp"


CameraComponent::CameraComponent(float foe, float ratio, float near, float far) {
    projection = glm::perspective(foe, ratio, near, far);
}

CameraComponent::CameraComponent(float left, float right, float up, float bottom, float near, float far) {
    projection = glm::ortho(left, right, bottom, up, near, far);
}
