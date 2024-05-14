//
// Created by wiktor on 11.05.23.
//

#ifndef WIKENGINE_BASICCUBE_H
#define WIKENGINE_BASICCUBE_H

#include "../Entity.h"
#include "../ScriptComponent.h"
#include "../TransformComponent.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../RigidbodyComponent.h"
#include <GL/glew.h>


class CubeScript : public ScriptComponent {
public:
    void Update(float deltaTime) override {
//        auto tranform = _entity->GetComponent<TransformComponent>(TransformComponentType);
//        auto mat = tranform->Matrix();
//        //tranform->SetMatrix(glm::rotate(tranform->Matrix(), (float) glm::radians(1.0), glm::vec3(1.0, 1, 1)));
    }

    void Setup() override {
    }
};

Entity *CreateBasicCube();

#endif //WIKENGINE_BASICCUBE_H
