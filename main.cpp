#include <iostream>
#include "Engine/Include/EngineCore.h"
#include "Engine/Src/Core/Helpers/BasicCube.h"
#include "Engine/Src/Core/LambertMaterial.h"
#include <glm/gtx/string_cast.hpp>

int main(void) {
    Engine engine(1280, 1024);
    engine.Setup();

    CameraComponent cameraComponent(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100000.0f);
    cameraComponent.SetActive(true);
    TransformComponent transformComponentCamera;
    Entity entityCamera;
    CameraFirstPersonScriptComponent cameraFirstPersonScriptComponent(entityCamera);
    entityCamera.AddUpdateComponent(cameraComponent);
    entityCamera.AddUpdateComponent(transformComponentCamera);
    entityCamera.AddUpdateComponent(cameraFirstPersonScriptComponent);

    Entity lightEntity;
    TransformComponent transformLight;
    auto matLight = transformLight.Matrix();
    transformComponentCamera.SetMatrix(glm::translate(matLight, glm::vec3(0, 2, 0)));
    lightEntity.AddUpdateComponent(transformLight);
    DirectionaLight light;
    light.dir.x = 0;
    light.dir.y = -1;
    light.dir.z = 0;
    lightEntity.AddUpdateComponent(light);

    Scene scene;
    scene.AddToScene(entityCamera);
    scene.AddToScene(lightEntity);

    auto objEntity2 = ReadFromObj("/home/wiktor/CLionProjects/wikengine/example/obj/css_assault/csAssult.obj");
    scene.AddToScene(*objEntity2);

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    engine.Run(scene);

    return 0;
}