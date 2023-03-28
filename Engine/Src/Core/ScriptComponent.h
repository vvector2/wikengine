//
// Created by wiktor on 20.02.23.
//

#ifndef WIKENGINE_SCRIPTCOMPONENT_H
#define WIKENGINE_SCRIPTCOMPONENT_H


#include "IComponent.h"
#include "Entity.h"

const std::string ScriptComponentTypeName = "ScriptComponent";

class ScriptComponent: public IComponent {
public:
    explicit ScriptComponent(Entity& _entity);
    std::string GetComponentType() override {return ScriptComponentTypeName;}
    virtual void Update(float deltaTime) = 0;
    virtual void Setup() = 0;
protected:
    Entity& entity;

};


#endif //WIKENGINE_SCRIPTCOMPONENT_H
