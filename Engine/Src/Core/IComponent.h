//
// Created by wiktor on 04.02.23.
//

#ifndef WIKENGINE_ICOMPONENT_H
#define WIKENGINE_ICOMPONENT_H


#include <string>

enum ComponentsType {
    TransformComponentType = 1, ScriptComponentType, MeshComponentType, MaterialComponentType, LightComponentType,
    CameraComponentType
};

class IComponent {
public:
    virtual ComponentsType GetComponentType() = 0;

    virtual ~IComponent() = default;
};


#endif //WIKENGINE_ICOMPONENT_H
