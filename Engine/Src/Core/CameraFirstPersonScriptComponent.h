//
// Created by wiktor on 20.02.23.
//

#ifndef WIKENGINE_CAMERAFIRSTPERSONSCRIPTCOMPONENT_H
#define WIKENGINE_CAMERAFIRSTPERSONSCRIPTCOMPONENT_H


#include "ScriptComponent.h"
#include "CameraFirstPerson.h"

class CameraFirstPersonScriptComponent : public ScriptComponent {
public:
    explicit CameraFirstPersonScriptComponent();

    void Update(float deltaTime) override;

    void Setup() override;

    ~CameraFirstPersonScriptComponent();

private:
    CameraFirstPerson *cameraFirstPerson;
    float lastY;
    float lastX;
    bool firstMouse;
};


#endif //WIKENGINE_CAMERAFIRSTPERSONSCRIPTCOMPONENT_H
