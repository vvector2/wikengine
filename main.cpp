#include <iostream>
#include "Engine/Include/EngineCore.h"
#include "Engine/Src/Core/Helpers/BasicCube.h"

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

    auto cube = CreateBasicCube();

    Scene scene;
    scene.AddToScene(*cube);
    scene.AddToScene(entityCamera);
    scene.AddToScene(lightEntity);

    //auto objEntity = ReadFromObj("../teapot.obj", shaderProgram);
    //auto objTransform = objEntity->GetComponent<TransformComponent>();
    //objTransform->SetMatrix(rotate(objTransform->Matrix(), - glm::pi<float>() /2 , glm::vec3(1,0,0) ));
    //scene.AddToScene(*objEntity);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    engine.Run(scene);

    return 0;
}