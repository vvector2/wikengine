//
// Created by wiktor on 06.02.23.
//

#include "MeshComponent.h"

MeshComponent::MeshComponent(std::vector<GLfloat> vertices, std::vector<GLuint> index) {
    glCreateBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (GLfloat), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &bufferIndexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof (GLuint), &index[0], GL_STATIC_DRAW);

    indicesN = index.size();
}

void MeshComponent::Active() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndexID);
}

void MeshComponent::Inactive() {
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshComponent::~MeshComponent() {
    glDeleteBuffers(1, &bufferID);
    glDeleteBuffers(1, &bufferIndexID);
}
