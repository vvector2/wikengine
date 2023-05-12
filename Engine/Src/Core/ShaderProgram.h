//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_SHADERPROGRAM_H
#define WIKENGINE_SHADERPROGRAM_H


#include <string>
#include "GL/glew.h"

class ShaderProgram {
public:
    ShaderProgram(std::string& vertexShader, std::string& fragmentShader);
    inline GLuint GetShaderProgramId() const {return shaderProgramId;}
    void Active();
    void Inactive();
private:
    GLuint LoadShader(std::string& shaderContent, GLenum shaderType);
    GLuint shaderProgramId;
};


#endif //WIKENGINE_SHADERPROGRAM_H
