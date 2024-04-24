//
// Created by wiktor on 02.02.23.
//

#ifndef WIKENGINE_ENTITY_H
#define WIKENGINE_ENTITY_H

#include <map>
#include <unordered_map>
#include "../../external/sole/sole.hpp"
#include "IComponent.h"

class Entity {
public:
    Entity();

    std::vector<Entity *> GetChilds();

    void AddChild(Entity &entity);

    void RemoveChild(sole::uuid id);

    template<class T>
    T *GetComponent(ComponentsType type) {
        if (components.find(type) == components.end())
            return nullptr;
        else
            return (T *) components[type];
    }

    void RemoveComponent(ComponentsType type) {
        auto component = components.find(type);
        if (component != components.end())
            throw std::runtime_error("First Remove existing component");

        components.erase(type);

        component->second->SetCurrentEntity(nullptr);
    }

    void AddUpdateComponent(IComponent &component) {
        if (components.find(component.GetComponentType()) != components.end())
            throw std::runtime_error("First Remove existing component");

        components[component.GetComponentType()] = &component;

        component.SetCurrentEntity(this);
    }

    void SetFather(Entity *father);

    Entity *GetFather();

    sole::uuid ID() const;

    ~Entity();

private:
    sole::uuid id;
    Entity *_father = nullptr;
    std::map<std::string, Entity *> childs;
    std::map<ComponentsType, IComponent *> components;
};


#endif //WIKENGINE_ENTITY_H
