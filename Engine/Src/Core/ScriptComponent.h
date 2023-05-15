//
// Created by wiktor on 20.02.23.
//

#ifndef WIKENGINE_SCRIPTCOMPONENT_H
#define WIKENGINE_SCRIPTCOMPONENT_H


#include "IComponent.h"
#include "Entity.h"

class ScriptComponent : public IComponent {
public:
    explicit ScriptComponent(Entity &_entity);

    ComponentsType GetComponentType() override { return ScriptComponentType; }

    virtual void Update(float deltaTime) = 0;

    virtual void Setup() = 0;

protected:
    Entity &entity;

};


#endif //WIKENGINE_SCRIPTCOMPONENT_H
