//
// Created by wiktor on 04.02.23.
//

#ifndef WIKENGINE_TRANSFORMCOMPONENT_H
#define WIKENGINE_TRANSFORMCOMPONENT_H


#include <string>
#include "IComponent.h"
#include <glm/glm.hpp>

const std::string TransformComponentTypeName = "TransformComponent";

class TransformComponent: public IComponent {
public:
    std::string GetComponentType() override {return TransformComponentTypeName;}
    glm::mat4  Matrix();
    void  SetMatrix(glm::mat4 _mat);
private:
    glm::mat4 mat;
};


#endif //WIKENGINE_TRANSFORMCOMPONENT_H
