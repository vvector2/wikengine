//
// Created by wiktor on 04.02.23.
//

#include "TransformComponent.h"

glm::mat4 TransformComponent::Matrix() {
    return mat;
}

void TransformComponent::SetMatrix(glm::mat4 _mat) {
    mat = _mat;
}
