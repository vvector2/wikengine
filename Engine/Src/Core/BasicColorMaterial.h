//
// Created by wiktor on 07.02.23.
//

#ifndef WIKENGINE_BASICCOLORMATERIAL_H
#define WIKENGINE_BASICCOLORMATERIAL_H


#include <vector>
#include "GL/glew.h"
#include "ShaderProgram.h"
#include "IComponent.h"
#include "glm/vec3.hpp"

class Material: public IComponent {
public:
    virtual void Active() = 0;
    virtual void InActive() = 0;
};

const std::string BasicColorMaterialTypeName = "BasicColorMaterial";

class BasicColorMaterial: public Material {
public:
    std::string GetComponentType() override {return BasicColorMaterialTypeName;}
    BasicColorMaterial(glm::vec3 _color, ShaderProgram _shaderProgram);
    void Active() override;
    void InActive() override;
    inline ShaderProgram GetShaderProgram() {return shaderProgram;};
private:
    ShaderProgram shaderProgram;
    glm::vec3 color;
};

const std::string SimpleTextureMaterialTypeName = "SimpleTextureMaterial";

class SimpleTextureMaterial: public Material {
public:
    std::string GetComponentType() override {return SimpleTextureMaterialTypeName;}
    SimpleTextureMaterial(ShaderProgram _shaderProgram, std::string texturePath, std::vector<GLfloat>& uv);
    void Active() override;
    void InActive() override;
    inline ShaderProgram GetShaderProgram() {return shaderProgram;};
    ~SimpleTextureMaterial();
private:
    ShaderProgram shaderProgram;
    GLuint textureId;
    GLuint textureUniformId;
    GLuint uvBufferId;
};


#endif //WIKENGINE_BASICCOLORMATERIAL_H
