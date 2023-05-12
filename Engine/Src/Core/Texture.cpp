//
// Created by wiktor on 11.05.23.
//

#include "Texture.h"

#include <utility>

#define STB_IMAGE_IMPLEMENTATION

#include "../../../external/stb_image/stb_image.h"

Texture::Texture(std::string _path) : path(std::move(_path)) {

}

void Texture::Load() {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
