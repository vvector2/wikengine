//
// Created by wiktor on 04.02.23.
//

#include "TransformComponent.h"
#include "Entity.h"
#include "Common.h"

glm::mat4 TransformComponent::Matrix() {
    return mat;
}

void TransformComponent::SetMatrix(glm::mat4 _mat) {
    mat = _mat;
}

glm::mat4 TransformComponent::WorldMatrix() {
    auto result = CalculateWorldMatrix(Matrix(), _entity);
    return result;
}

glm::mat4 TransformComponent::CalculateWorldMatrix(glm::mat4 matCurrent, Entity *currentEntity) {
    auto father = currentEntity->GetFather();
    if (father == nullptr) return matCurrent;
    else {
        auto fatherTransform = father->GetComponent<TransformComponent>(TransformComponentType);
        auto fatherMatrix = fatherTransform->Matrix();
        auto newMat = matCurrent * fatherMatrix;
        return CalculateWorldMatrix(newMat, father);
    }
}
