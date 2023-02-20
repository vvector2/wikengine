//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_SIMPLEFORWARDRENDERER_H
#define WIKENGINE_SIMPLEFORWARDRENDERER_H


#include "Scene.h"
#include "CameraComponent.h"

class SimpleForwardRenderer {
public:
    void Render(Scene& scene);
private:
    void RenderEntity(Entity& entity, glm::mat4 activeCameraProjection);
    glm::mat4 GetActiveCameraProjection(Scene& scene);
};


#endif //WIKENGINE_SIMPLEFORWARDRENDERER_H
