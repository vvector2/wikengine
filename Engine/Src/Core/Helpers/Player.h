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

    ~Player() override;

private:
    CameraFirstPerson *cameraFirstPerson;
    float lastY;
    float lastX;
    bool firstMouse;
};


#endif //WIKENGINE_PLAYER_H
