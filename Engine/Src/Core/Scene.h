//
// Created by wiktor on 04.02.23.
//

#ifndef WIKENGINE_SCENE_H
#define WIKENGINE_SCENE_H


#include "Entity.h"
#include "../../external/sole/sole.hpp"
#include <reactphysics3d/reactphysics3d.h>

class Scene {
public:
    void AddToScene(Entity &entity);

    void RemoveFromScene(sole::uuid id);

    std::vector<Entity *> GetChilds();

private:
    Entity head;
};


#endif //WIKENGINE_SCENE_H
