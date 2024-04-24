#include "Engine/Include/EngineCore.h"
#include "Engine/Src/Core/Helpers/Player.h"

int main(void) {
    Engine engine(1280, 1024);
    engine.Setup();

    //player
    Entity player;

    Entity entityCamera;
    CameraComponent cameraComponent(glm::radians(45.f), 4.0f / 3.0f, 0.1f, 100000.0f);
    TransformComponent transformComponentCamera;
    entityCamera.AddUpdateComponent(cameraComponent);
    entityCamera.AddUpdateComponent(transformComponentCamera);


    RigidbodyComponent rigidBodyComponent;
    rigidBodyComponent.SetBodyType(reactphysics3d::BodyType::DYNAMIC);
    reactphysics3d::CapsuleShape *capsuleShape = Engine::physicsCommon.createCapsuleShape(0.01, 0.02);
    rigidBodyComponent.AddCollider(capsuleShape);

    TransformComponent transformComponentPlayer;

    Player playerScript;

    player.AddUpdateComponent(playerScript);
    player.AddUpdateComponent(transformComponentPlayer);
    player.AddUpdateComponent(rigidBodyComponent);

    player.AddChild(entityCamera);

    transformComponentPlayer.SetMatrix(glm::translate(transformComponentPlayer.Matrix(), glm::vec3(0, 2, 0)));

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
    auto map = deserializerObj.CreateEntity(true, true, true);

    // scene
    Scene scene;
    scene.AddToScene(player);
    scene.AddToScene(lightEntity);
    scene.AddToScene(*debugCollider);
    scene.AddToScene(*map);
    scene.SetActiveCamera(entityCamera);

    engine.Run(scene);

    return 0;
}