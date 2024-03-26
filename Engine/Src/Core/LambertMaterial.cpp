//
// Created by wiktor on 11.05.23.
//

#include "LambertMaterial.h"
#include "Common.h"

LambertMaterial::LambertMaterial() {
    auto vertexShader = ReadFile("../Engine/Src/Core/Shaders/BasicLambert.vs.glsl");
    auto fragmentShader = ReadFile("../Engine/Src/Core/Shaders/BasicLambert.fs.glsl");
    shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    cameraMatrixUniformId = glGetUniformLocation(shaderProgram->GetShaderProgramId(), CameraMatrixUniformName.c_str());
    worldMatrixUniformId = glGetUniformLocation(shaderProgram->GetShaderProgramId(), WorldMatrixUniformName.c_str());
    directionalLightUniformId = glGetUniformLocation(shaderProgram->GetShaderProgramId(),
                                                     directionalLightUniformName.c_str());
    enableLightUniformId = glGetUniformLocation(shaderProgram->GetShaderProgramId(), enableLightUniformName.c_str());
}

void LambertMaterial::SetTexture(Texture &_texture) {
    textureUniformId = glGetUniformLocation(shaderProgram->GetShaderProgramId(), TextureSampler0UniformName.c_str());
    textureEnableUniformId = glGetUniformLocation(shaderProgram->GetShaderProgramId(),
                                                  TextureEnableUniformName.c_str());
    texture = &_texture;
}

void LambertMaterial::ClearTexture() {
    texture = nullptr;
}

void LambertMaterial::Active(glm::mat4 &cameraMatrix, glm::mat4 &worldMatrix, DirectionaLight &directionalLight, GLboolean enableLighting) {
    shaderProgram->Active();

    glUniform3f(directionalLightUniformId, directionalLight.dir.x, directionalLight.dir.y, directionalLight.dir.z);
    glUniformMatrix4fv(cameraMatrixUniformId, 1, GL_FALSE, &cameraMatrix[0][0]);
    glUniformMatrix4fv(worldMatrixUniformId, 1, GL_FALSE, &worldMatrix[0][0]);
    glUniform1i(enableLightUniformId, enableLighting ? 1 : 0);

    if (texture != nullptr) {
        glUniform1i(textureEnableUniformId, 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
        glUniform1i(textureUniformId, 0);
    } else {
        glUniform1i(textureEnableUniformId, 0);
    }
}

void LambertMaterial::Inactive() {
    shaderProgram->Inactive();

    glBindTexture(GL_TEXTURE_2D, 0);
}

LambertMaterial::~LambertMaterial() {
    delete shaderProgram;
}
