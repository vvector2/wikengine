#include "Engine/Include/EngineCore.h"

int main(void) {
    Engine engine(1280, 1024);
    engine.Setup();

    //camera
    Entity entityCamera;
    CameraComponent cameraComponent(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100000.0f);
    TransformComponent transformComponentCamera;
    CameraFirstPersonScriptComponent cameraFirstPersonScriptComponent;
    entityCamera.AddUpdateComponent(cameraComponent);
    entityCamera.AddUpdateComponent(transformComponentCamera);
    entityCamera.AddUpdateComponent(cameraFirstPersonScriptComponent);

    //player
    Entity player;

    Entity entityCameraPlayer;
    CameraComponent cameraComponentPlayer(glm::radians(45.f), 4.0f / 3.0f, 0.0001f, 100.0f);
    TransformComponent transformComponentCameraPlayer;
    entityCameraPlayer.AddUpdateComponent(cameraComponentPlayer);
    entityCameraPlayer.AddUpdateComponent(transformComponentCameraPlayer);

    RigidbodyComponent rigidBodyComponent;
    rigidBodyComponent.GetRigidBody()->setType(reactphysics3d::BodyType::DYNAMIC);
    auto *capsuleShape = Engine::physicsCommon.createCapsuleShape(0.01, 0.1);
    rigidBodyComponent.GetRigidBody()->addCollider(capsuleShape, reactphysics3d::Transform::identity());

    TransformComponent transformComponentPlayer;

    Player playerScript;
    playerScript.SetCameraEntity(&entityCameraPlayer);

    player.AddUpdateComponent(playerScript);
    player.AddUpdateComponent(transformComponentPlayer);
    player.AddUpdateComponent(rigidBodyComponent);

    player.AddChild(entityCameraPlayer);

    transformComponentPlayer.SetMatrix(glm::translate(transformComponentPlayer.Matrix(), glm::vec3(0, 2, 0.4)));

    //light
    Entity lightEntity;
    TransformComponent transformLight;
    auto matLight = transformLight.Matrix();
    lightEntity.AddUpdateComponent(transformLight);
    DirectionaLight light;
    light.dir.x = 0;
    light.dir.y = -1;
    light.dir.z = 0;
    lightEntity.AddUpdateComponent(light);

    // debug collider
    auto debugCollider = DebugCollider::Create();

    // map
    DeserializerObj deserializerObj;
    deserializerObj.LoadFile("/home/wiktor/CLionProjects/wikengine/example/obj/css_assault/csAssult.obj");
    deserializerObj.LoadCollider("/home/wiktor/CLionProjects/wikengine/example/obj/css_assault/colliders.obj");
    auto map = deserializerObj.CreateEntity(true);

    // surface
//    auto surfaceEntity = CreateBasicCube();
//    auto surfaceTransform = surfaceEntity->GetComponent<TransformComponent>(TransformComponentType);
//    auto surfaceRigidBody = surfaceEntity->GetComponent<RigidbodyComponent>(RigidbodyComponentType);
//    auto surfaceMatrix = surfaceTransform->Matrix();
//
//    surfaceRigidBody->GetRigidBody()->setType(reactphysics3d::BodyType::STATIC);
//    surfaceTransform->SetMatrix(
//            glm::scale(glm::translate(surfaceMatrix, glm::vec3(0, -1.0f, 0)), glm::vec3(10, 0.1, 10)));


    // scene
    Scene scene;
    scene.AddToScene(lightEntity);
    //scene.AddToScene(*debugCollider);
    //scene.AddToScene(*surfaceEntity);
    //scene.AddToScene(entityCamera);
    scene.AddToScene(player);
    scene.AddToScene(*map);

    scene.SetActiveCamera(entityCameraPlayer);

    engine.Run(scene);

    return 0;
}