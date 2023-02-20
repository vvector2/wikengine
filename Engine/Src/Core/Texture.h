//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_TEXTURE_H
#define WIKENGINE_TEXTURE_H


#include <string>
#include <vector>
#include "GL/glew.h"

class Texture {
public:
    Texture(std::string _path, std::vector<GLfloat> _uv);
    void Load();
    void Bind();
private:
    std::vector<GLfloat> uv;
    std::string path;
    GLuint textureId = -1;
};


#endif //WIKENGINE_TEXTURE_H
