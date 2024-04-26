//
// Created by wiktor on 23.04.24.
//

#ifndef WIKENGINE_PLAYER_H
#define WIKENGINE_PLAYER_H


#include "../ScriptComponent.h"
#include "../CameraFirstPerson.h"

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
};


#endif //WIKENGINE_PLAYER_H
