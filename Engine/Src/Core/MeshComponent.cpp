//
// Created by wiktor on 06.02.23.
//

#include "MeshComponent.h"

MeshComponent::MeshComponent(std::vector<GLfloat> &vertices,
                             std::vector<GLfloat> &color,
                             std::vector<GLfloat> &normal,
                             std::vector<GLfloat> &uv,
                             std::vector<GLuint> &index) {

    glCreateBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &colorBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, colorBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, color.size() * sizeof(GLfloat), &color[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalsBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalsBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, normal.size() * sizeof(GLfloat), &normal[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uvBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, uv.size() * sizeof(GLfloat), &uv[0], GL_STATIC_DRAW);


    glGenBuffers(1, &bufferIndexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint), &index[0], GL_STATIC_DRAW);

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
            (void *) 0
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) 0
    );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBufferId);
    glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) 0
    );

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
    glVertexAttribPointer(
            3,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) 0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndexID);
}

void MeshComponent::Inactive() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshComponent::~MeshComponent() {
    glDeleteBuffers(1, &bufferID);
    glDeleteBuffers(1, &colorBufferId);
    glDeleteBuffers(1, &normalsBufferId);
    glDeleteBuffers(1, &uvBufferId);
    glDeleteBuffers(1, &bufferIndexID);
}

void MeshComponent::Render() {
    glDrawElements(
            GL_TRIANGLES,
            indicesN,
            GL_UNSIGNED_INT,
            (void *) 0
    );
}
