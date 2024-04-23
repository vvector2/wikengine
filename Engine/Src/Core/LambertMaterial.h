//
// Created by wiktor on 11.05.23.
//

#ifndef WIKENGINE_LAMBERTMATERIAL_H
#define WIKENGINE_LAMBERTMATERIAL_H


#include "Texture.h"
#include "ShaderProgram.h"
#include "IComponent.h"
#include "glm/detail/type_mat.hpp"
#include "glm/vec3.hpp"
#include "DirectionaLight.h"

const std::string TextureSampler0UniformName = "textureSampler0";
const std::string TextureEnableUniformName = "textureEnableUnifornName";
const std::string CameraMatrixUniformName = "cameraMatrix";
const std::string WorldMatrixUniformName = "worldMatrix";
const std::string directionalLightUniformName = "directionalLight";
const std::string enableLightUniformName = "enableLight";

class LambertMaterial : public IComponent {
public:
    ComponentsType GetComponentType() override { return MaterialComponentType; }

    LambertMaterial();

    ~LambertMaterial() override;

    void SetTexture(Texture &_texture);

    void ClearTexture();

    void Active(glm::mat4 &cameraMatrix, glm::mat4 &worldMatrix, DirectionaLight &directionalLight,
                GLboolean enableLighting);

    void Inactive();

    bool WireFrame = false;

    bool Disabled = false;

private:
    ShaderProgram *shaderProgram = nullptr;
    GLint textureUniformId = -1;
    GLint textureEnableUniformId = -1;
    GLint cameraMatrixUniformId = -1;
    GLint directionalLightUniformId = -1;
    GLint worldMatrixUniformId = -1;
    GLint enableLightUniformId = -1;
    Texture *texture = nullptr;
};


#endif //WIKENGINE_LAMBERTMATERIAL_H
