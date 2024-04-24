//
// Created by wiktor on 04.02.23.
//

#ifndef WIKENGINE_SCENE_H
#define WIKENGINE_SCENE_H


#include "Entity.h"
#include "../../external/sole/sole.hpp"
#include "TransformComponent.h"
#include <reactphysics3d/reactphysics3d.h>

class Scene {
public:
    Scene();

    void AddToScene(Entity &entity);

    void RemoveFromScene(sole::uuid id);

    std::vector<Entity *> GetChilds();

    void SetActiveCamera(Entity &entity);

    Entity *GetActiveCamera();

private:
    Entity head;
    Entity *camera = nullptr;
    TransformComponent tranformComponent;
};


#endif //WIKENGINE_SCENE_H
