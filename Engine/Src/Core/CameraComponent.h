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

    inline void SetActive(bool _active) { active = _active; };

    inline bool IsActive() const { return active; };

    inline glm::mat4 Projection() { return projection; };
private:
    bool active = false;
    glm::mat4 projection;
};


#endif //WIKENGINE_CAMERACOMPONENT_H
