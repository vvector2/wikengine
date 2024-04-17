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

    DeserializerObj deserializerObj;
    deserializerObj.LoadFile("/home/wiktor/CLionProjects/wikengine/example/obj/css_assault/csAssult.obj");
    auto objEntity2 = deserializerObj.CreateEntity(true, true, true);
    scene.AddToScene(*objEntity2);

    engine.Run(scene);

    return 0;
}