//
// Created by wiktor on 06.02.23.
//

#ifndef WIKENGINE_MESHCOMPONENT_H
#define WIKENGINE_MESHCOMPONENT_H


#include <vector>
#include "GL/glew.h"
#include "IComponent.h"

class MeshComponent : public IComponent {
public:
    ComponentsType GetComponentType() override { return MeshComponentType; }

    MeshComponent(std::vector<GLfloat> &vertices,
                  std::vector<GLfloat> &color,
                  std::vector<GLfloat> &normal,
                  std::vector<GLfloat> &uv,
                  std::vector<GLuint> &index);

    void Active();

    void Render();

    void Inactive();

    void Update(std::vector<GLfloat> &vertices,
                std::vector<GLfloat> &color,
                std::vector<GLfloat> &normal,
                std::vector<GLfloat> &uv,
                std::vector<GLuint> &index);

    ~MeshComponent();

    GLboolean IsNormalExists() { return normalExists; }

    GLboolean IsUVExists() { return uvExists; }

private:
    GLuint indicesN;

    GLuint bufferID;
    GLuint colorBufferId;
    GLuint bufferIndexID;
    GLuint uvBufferId;
    GLuint normalsBufferId;

    GLboolean normalExists;
    GLboolean uvExists;
};


#endif //WIKENGINE_MESHCOMPONENT_H
