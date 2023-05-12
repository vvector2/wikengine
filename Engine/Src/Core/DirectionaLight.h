//
// Created by wiktor on 12.05.23.
//

#ifndef WIKENGINE_DIRECTIONALIGHT_H
#define WIKENGINE_DIRECTIONALIGHT_H


#include "IComponent.h"
#include "glm/vec3.hpp"

const std::string DirectionaLightTypeName = "DirectionaLight";

class DirectionaLight : public IComponent {
public:
    std::string GetComponentType() override { return DirectionaLightTypeName; }

    glm::vec3 dir;
};


#endif //WIKENGINE_DIRECTIONALIGHT_H
