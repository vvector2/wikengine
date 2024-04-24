#include <iostream>
#include "SimpleForwardRenderer.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "Common.h"
#include "CameraComponent.h"
#include "LambertMaterial.h"

void SimpleForwardRenderer::Render(Scene &scene) {
    auto activeCameraProjection = GetActiveCameraProjection(scene);
    auto directionalLight = GetDirectionalLightFromScene(scene);

    glm::mat4 mat;
    auto childs = scene.GetChilds();
    for (auto child: childs) {
        RenderEntity(*child, activeCameraProjection, *directionalLight, mat);
    }
}

void SimpleForwardRenderer::RenderEntity(Entity &entity, glm::mat4 &activeCameraProjection,
                                         DirectionaLight &directionalLight, const glm::mat4 &fatherMatrix) {
    auto mesh = entity.GetComponent<MeshComponent>(MeshComponentType);
    auto transform = entity.GetComponent<TransformComponent>(TransformComponentType);
    auto lambertMaterial = entity.GetComponent<LambertMaterial>(MaterialComponentType);

    if (mesh != nullptr && transform != nullptr && lambertMaterial != nullptr && !lambertMaterial->Disabled) {

        auto transformMatrix = transform->Matrix();
        auto entityMatrix = fatherMatrix * transformMatrix;
        lambertMaterial->Active(activeCameraProjection, entityMatrix, directionalLight, mesh->IsNormalExists());

        mesh->Active();
        mesh->Render();
        mesh->Inactive();

        lambertMaterial->Inactive();
    }

    if (transform != nullptr) {
        for (auto child: entity.GetChilds()) {
            RenderEntity(*child, activeCameraProjection, directionalLight, transform->Matrix());
        }
    }
}

glm::mat4 SimpleForwardRenderer::GetActiveCameraProjection(Scene &scene) {
    auto cameraEntity = scene.GetActiveCamera();

    if (cameraEntity != nullptr) {
        auto camera = cameraEntity->GetComponent<CameraComponent>(CameraComponentType);
        auto cameraTransform = cameraEntity->GetComponent<TransformComponent>(TransformComponentType);
        auto activeCameraProjection = camera->Projection() * cameraTransform->WorldMatrix();
        return activeCameraProjection;
    } else
        throw std::runtime_error("No active camera on scene");
}

DirectionaLight *SimpleForwardRenderer::GetDirectionalLightFromScene(Scene &scene) {
    auto childs = scene.GetChilds();
    auto directionalLights = Filter<Entity *>(scene.GetChilds(), [](Entity *entity) {
                                                  auto camera = entity->GetComponent<DirectionaLight>(LightComponentType);
                                                  return camera != nullptr;
                                              }
    );
    return directionalLights.empty() ? nullptr : directionalLights[0]->GetComponent<DirectionaLight>(
            LightComponentType);
}


