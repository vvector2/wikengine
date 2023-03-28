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
    MeshComponent(std::vector<GLfloat>& vertices, std::vector<GLuint>& index);
    void Active();
    void Inactive();
    inline GLuint GetIndicesN() const {return indicesN;}
    ~MeshComponent();
private:
    GLuint indicesN;
    GLuint bufferID;
    GLuint bufferIndexID;
};


#endif //WIKENGINE_MESHCOMPONENT_H
