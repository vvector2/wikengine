
#include "ShaderUtility.h"
#include "Common.h"

GLuint LoadShader(const std::string& filePath, GLenum shaderType){
    GLuint vertexShaderID = glCreateShader(shaderType);
    auto vertexShaderCode = ReadFile(filePath);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    char const * vertexShaderCodePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexShaderCodePointer, nullptr);
    glCompileShader(vertexShaderID);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> vertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, InfoLogLength, nullptr, &vertexShaderErrorMessage[0]);
        std::string vertexShaderErrorMessageStr = vertexShaderErrorMessage.data();
        throw std::runtime_error("Failed to load shader " + filePath + "\n Error: " + vertexShaderErrorMessageStr);
    }
    return vertexShaderID;
}