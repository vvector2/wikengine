//
// Created by wiktor on 07.02.23.
//

#include <vector>
#include <stdexcept>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexShader, std::string fragmentShader) {
    auto vertextShaderId = LoadShader(vertexShader, GL_VERTEX_SHADER);
    auto fragmentShaderId = LoadShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLint result = GL_FALSE;
    int infoLogLength;

    GLuint programId = glCreateProgram();

    glAttachShader(programId, vertextShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(programId, vertextShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertextShaderId);
    glDeleteShader(fragmentShaderId);

    shaderProgramId = programId;

    matrixIdUniform = glGetUniformLocation(programId, mvpUniformName.c_str());
}

GLuint ShaderProgram::LoadShader(std::string shaderContent, GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    char const * vertexShaderCodePointer = shaderContent.c_str();
    glShaderSource(shaderID, 1, &vertexShaderCodePointer, nullptr);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> vertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shaderID, InfoLogLength, nullptr, &vertexShaderErrorMessage[0]);
        std::string vertexShaderErrorMessageStr = vertexShaderErrorMessage.data();
        throw std::runtime_error("Failed to load shader " + shaderContent + "\n Error: " + vertexShaderErrorMessageStr);
    }
    return shaderID;
}

void ShaderProgram::Active() {
    glUseProgram(shaderProgramId);
}

void ShaderProgram::Inactive() {
    glUseProgram(0);
}
