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
    MeshComponent(std::vector<GLfloat>& vertices, std::vector<GLuint>& index, GLboolean _line = false);
    void Active();
    void Render();
    void Inactive();
    ~MeshComponent();
private:
    GLuint indicesN;
    GLuint bufferID;
    GLuint bufferIndexID;
    GLboolean line;
};


#endif //WIKENGINE_MESHCOMPONENT_H
