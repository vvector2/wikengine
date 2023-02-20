//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_SHADERPROGRAM_H
#define WIKENGINE_SHADERPROGRAM_H


#include <string>
#include "GL/glew.h"

const std::string mvpUniformName = "mvp";

class ShaderProgram {
public:
    ShaderProgram(std::string vertexShader, std::string fragmentShader);
    inline GLuint GetShaderProgramId() const {return shaderProgramId;}
    inline GLuint GetMatrixIdUniform() const {return matrixIdUniform;}
    void Active();
    void Inactive();
private:
    GLuint LoadShader(std::string shaderContent, GLenum shaderType);
    GLuint shaderProgramId;
    GLuint matrixIdUniform;
};


#endif //WIKENGINE_SHADERPROGRAM_H
