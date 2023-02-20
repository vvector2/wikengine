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
    std::vector<Entity> GetChilds();
    void AddChild(Entity& entity);
    void RemoveChild(sole::uuid id);

    template <class T>
    T* GetComponent(){
        return (T*)components[typeid(T).name()];
    }

    template <class T>
    void RemoveComponent() {
        components.erase(typeid(T).name());
    }

    template <typename T>
    void AddUpdateComponent(T &component) {
        components[typeid(T).name()] = &component;
    }

    sole::uuid ID() const;
private:
    sole::uuid id;
    std::map<std::string , Entity*> childs;
    std::unordered_map<std::string, IComponent*> components;
};


#endif //WIKENGINE_ENTITY_H
