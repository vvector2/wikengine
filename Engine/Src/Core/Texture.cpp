//
// Created by wiktor on 07.02.23.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stb_image/stb_image.h"

Texture::Texture(std::string _path, std::vector<GLfloat> _uv) : uv(_uv), path(_path) {

}

void Texture::Load() {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}
