//
// Created by wiktor on 11.05.23.
//

#ifndef WIKENGINE_TEXTURE_H
#define WIKENGINE_TEXTURE_H

#include <string>
#include "GL/glew.h"


class Texture {
public:
    explicit Texture(std::string _path);

    void Load();

    GLuint GetTextureId() const { return textureId; }

private:
    std::string path;
    GLuint textureId = -1;
};

#endif //WIKENGINE_TEXTURE_H
