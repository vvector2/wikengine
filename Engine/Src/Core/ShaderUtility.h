#ifndef WIKENGINE_SHADERUTILITY_H
#define WIKENGINE_SHADERUTILITY_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint LoadShader(const std::string& filePath, GLenum shaderType);

#endif //WIKENGINE_SHADERUTILITY_H