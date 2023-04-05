//
// Created by wiktor on 07.02.23.
//

#include "BasicColorMaterial.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../../external/stb_image/stb_image.h"

void BasicColorMaterial::Active() {
    shaderProgram.Active();
}

BasicColorMaterial::BasicColorMaterial(glm::vec3 _color, ShaderProgram _shaderProgram): shaderProgram(_shaderProgram), color(_color) {

}

void BasicColorMaterial::InActive() {
    shaderProgram.Inactive();
}

SimpleTextureMaterial::SimpleTextureMaterial(ShaderProgram _shaderProgram, std::string texturePath,  std::vector<GLfloat>& uv): shaderProgram(_shaderProgram) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    textureUniformId  = glGetUniformLocation(shaderProgram.GetShaderProgramId(), "textureSampler0");

    glGenBuffers(1, &uvBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof (GLuint), &uv[0], GL_STATIC_DRAW);

}

void SimpleTextureMaterial::Active() {
    shaderProgram.Active();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(textureUniformId, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );
}

void SimpleTextureMaterial::InActive() {
    shaderProgram.Inactive();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(1);
}

SimpleTextureMaterial::~SimpleTextureMaterial() {
    glDeleteTextures(1, &textureId);
}
