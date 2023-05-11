#include <iostream>
#include "SimpleForwardRenderer.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "BasicColorMaterial.h"
#include "Common.h"
#include "CameraComponent.h"

void SimpleForwardRenderer::Render(Scene& scene) {
    auto activeCameraProjection = GetActiveCameraProjection(scene);

    auto childs = scene.GetChilds();
    for (auto child: childs) {
        RenderEntity(*child, activeCameraProjection);
    }
}

void SimpleForwardRenderer::RenderEntity(Entity& entity, glm::mat4 activeCameraProjection) {
    auto mesh = entity.GetComponent<MeshComponent>();
    auto transform = entity.GetComponent<TransformComponent>();
    auto basicColorMaterial = entity.GetComponent<BasicColorMaterial>();
    //auto basicTextureMaterial = entity.GetComponent<SimpleTextureMaterial>();
    if (mesh != nullptr && transform != nullptr && basicColorMaterial != nullptr ) {
        basicColorMaterial->Active();

        auto mvp =  activeCameraProjection * transform->Matrix();
        glUniformMatrix4fv(basicColorMaterial->GetShaderProgram().GetMatrixIdUniform(), 1, GL_FALSE, &mvp[0][0]);

        mesh->Active();
        mesh->Render();
        mesh->Inactive();

        basicColorMaterial->InActive();
    }


    for (auto child: entity.GetChilds()) {
        RenderEntity(*child, activeCameraProjection * transform->Matrix());
    }
}

glm::mat4 SimpleForwardRenderer::GetActiveCameraProjection(Scene& scene) {
    auto childs = scene.GetChilds();
    auto cameras = Filter<Entity*>(scene.GetChilds(),  [](Entity* entity){
        auto camera = entity->GetComponent<CameraComponent>();
        return camera != nullptr && camera->IsActive();
        }
    );
    if (!cameras.empty()){
        auto camera = cameras[0]->GetComponent<CameraComponent>();
        auto cameraTransform = cameras[0]->GetComponent<TransformComponent>();
        auto activeCameraProjection = camera->Projection() * cameraTransform->Matrix();
        return activeCameraProjection;
    }
    else
        throw std::runtime_error("No active camera on scene");
}
