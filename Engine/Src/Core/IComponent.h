//
// Created by wiktor on 04.02.23.
//

#ifndef WIKENGINE_ICOMPONENT_H
#define WIKENGINE_ICOMPONENT_H

class Entity;

#include <string>

enum ComponentsType {
    TransformComponentType = 1, ScriptComponentType, MeshComponentType, MaterialComponentType, LightComponentType,
    CameraComponentType, RigidbodyComponentType, ColliderComponentType
};

class IComponent {
public:
    virtual ComponentsType GetComponentType() = 0;

    virtual ~IComponent() = default;

    void SetCurrentEntity(Entity *entity) { _entity = entity; }

protected:

    Entity *_entity = nullptr;

};


#endif //WIKENGINE_ICOMPONENT_H
