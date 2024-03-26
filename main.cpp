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

    Texture texture("../kot.png");
    texture.Load();
    for (int i = 0; i < 1; i++) {
        auto cube = CreateBasicCube();

        auto transformComponent = cube->GetComponent<TransformComponent>(TransformComponentType);
        auto matrixCube2 = transformComponent->Matrix();
        matrixCube2 = translate(matrixCube2, glm::vec3(get_random() * 10, get_random() * 10, get_random() * 10));
        //transformComponent->SetMatrix(matrixCube2);

        if (get_random() > 0.5) {
            auto lambertMaterial = cube->GetComponent<LambertMaterial>(MaterialComponentType);
            lambertMaterial->SetTexture(texture);
        }

        scene.AddToScene(*cube);
    }

    auto plane = CreateBasicCube();
    auto planeTransformComponent = plane->GetComponent<TransformComponent>(TransformComponentType);
    auto planeMatrix = planeTransformComponent->Matrix();
    planeMatrix = scale(planeMatrix, glm::vec3(3, 0.05, 3));
    planeMatrix = translate(planeMatrix, glm::vec3(0, -40, 0));
    planeTransformComponent->SetMatrix(planeMatrix);
    plane->RemoveComponent(ScriptComponentType);
    scene.AddToScene(*plane);

    auto objEntity = ReadFromObj("../teapot.obj");
    auto objTransform = objEntity->GetComponent<TransformComponent>(TransformComponentType);
    //objTransform->SetMatrix(rotate(objTransform->Matrix(), - glm::pi<float>() /2 , glm::vec3(1,0,0) ));
    objTransform->SetMatrix(translate(objTransform->Matrix(), glm::vec3(5 ,1 ,1)));

    std::cout << glm::to_string(objTransform->Matrix()) << std::endl;
    scene.AddToScene(*objEntity);


    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    engine.Run(scene);

    return 0;
}