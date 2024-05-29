//
// Created by wiktor on 23.04.24.
//

#ifndef WIKENGINE_PLAYER_H
#define WIKENGINE_PLAYER_H


#include "../ScriptComponent.h"
#include "../CameraFirstPerson.h"

const float PLAYER_MOVEMENT_SPEED = 10;

class Player : public ScriptComponent {
public:

    void Update(float deltaTime) override;

    void Setup() override;

    void SetCameraEntity(Entity *entity);

    ~Player() override;

private:
    float lastY;
    float lastX;
    bool firstMouse;

    Entity *cameraEntity;
    CameraFirstPerson *cameraFirstPerson;

    void HandleMovement(float deltaTime);

    void HandleCamera(float deltaTime);

};


#endif //WIKENGINE_PLAYER_H
