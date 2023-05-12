//
// Created by wiktor on 06.02.23.
//

#ifndef WIKENGINE_MESHCOMPONENT_H
#define WIKENGINE_MESHCOMPONENT_H


#include <vector>
#include "GL/glew.h"
#include "IComponent.h"

const std::string MeshComponentTypeName = "MeshComponent";

class MeshComponent: public IComponent {
public:
    std::string GetComponentType() override {return MeshComponentTypeName;}
    MeshComponent(std::vector<GLfloat>& vertices,
                  std::vector<GLfloat>& color,
                  std::vector<GLfloat>& normal,
                  std::vector<GLfloat>& uv,
                  std::vector<GLuint>& index);
    void Active();
    void Render();
    void Inactive();
    ~MeshComponent();
private:
    GLuint indicesN;

    GLuint bufferID;
    GLuint colorBufferId;
    GLuint bufferIndexID;
    GLuint uvBufferId;
    GLuint normalsBufferId;
};


#endif //WIKENGINE_MESHCOMPONENT_H
