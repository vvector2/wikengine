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

    auto childs = scene.GetChilds();
    for (auto child: childs) {
        RenderEntity(*child, activeCameraProjection, *directionalLight);
    }
}

void SimpleForwardRenderer::RenderEntity(Entity &entity, glm::mat4 &activeCameraProjection,
                                         DirectionaLight &directionalLight) {
    auto mesh = entity.GetComponent<MeshComponent>(MeshComponentType);
    auto transform = entity.GetComponent<TransformComponent>(TransformComponentType);
    auto lambertMaterial = entity.GetComponent<LambertMaterial>(MaterialComponentType);

    if (mesh != nullptr && transform != nullptr && lambertMaterial != nullptr) {

        auto transformMatrix = transform->Matrix();
        lambertMaterial->Active(activeCameraProjection, transformMatrix, directionalLight);

        mesh->Active();
        mesh->Render();
        mesh->Inactive();

        lambertMaterial->Inactive();
    }


    for (auto child: entity.GetChilds()) {
        RenderEntity(*child, activeCameraProjection, directionalLight);
    }
}

glm::mat4 SimpleForwardRenderer::GetActiveCameraProjection(Scene &scene) {
    auto childs = scene.GetChilds();
    auto cameras = Filter<Entity *>(scene.GetChilds(), [](Entity *entity) {
                                        auto camera = entity->GetComponent<CameraComponent>(CameraComponentType);
                                        return camera != nullptr && camera->IsActive();
                                    }
    );
    if (!cameras.empty()) {
        auto camera = cameras[0]->GetComponent<CameraComponent>(CameraComponentType);
        auto cameraTransform = cameras[0]->GetComponent<TransformComponent>(TransformComponentType);
        auto activeCameraProjection = camera->Projection() * cameraTransform->Matrix();
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


