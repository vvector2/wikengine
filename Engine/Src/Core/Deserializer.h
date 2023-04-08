//
// Created by wiktor on 20.02.23.
//

#ifndef WIKENGINE_DESERIALIZER_H
#define WIKENGINE_DESERIALIZER_H

#include "Entity.h"
#include "ShaderProgram.h"

std::vector<Entity*> ReadFromObj(const std::string& path, ShaderProgram &shaderProgramBasictexture);


#endif //WIKENGINE_DESERIALIZER_H
