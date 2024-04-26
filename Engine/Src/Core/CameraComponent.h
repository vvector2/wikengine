//
// Created by wiktor on 14.02.23.
//

#ifndef WIKENGINE_CAMERACOMPONENT_H
#define WIKENGINE_CAMERACOMPONENT_H


#include "IComponent.h"
#include <glm/glm.hpp>

class CameraComponent : public IComponent {
public:
    ComponentsType GetComponentType() override { return CameraComponentType; }

    CameraComponent(float foe, float ratio, float near, float far);

    CameraComponent(float left, float right, float up, float down, float near, float far);

    inline glm::mat4 Projection() { return projection; };

    glm::mat4 View();

private:
    glm::mat4 projection;
};


#endif //WIKENGINE_CAMERACOMPONENT_H
