//
// Created by wiktor on 07.02.23.
//

#include "BasicColorMaterial.h"

void BasicColorMaterial::Active() {
    shaderProgram.Active();
}

BasicColorMaterial::BasicColorMaterial(glm::vec3 _color, ShaderProgram _shaderProgram): shaderProgram(_shaderProgram), color(_color) {

}

void BasicColorMaterial::InActive() {
    shaderProgram.Inactive();
}
