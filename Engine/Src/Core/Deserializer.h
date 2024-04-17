//
// Created by wiktor on 20.02.23.
//

#ifndef WIKENGINE_DESERIALIZER_H
#define WIKENGINE_DESERIALIZER_H

#include "Entity.h"
#include "ShaderProgram.h"
#include "../../../external/tinyobj/tiny_obj_loader.h"
#include "LambertMaterial.h"

class DeserializerObj {
public:

    void LoadFile(const std::string &path);

    Entity *CreateEntity(bool loadTexture, bool scaleVertices, bool addConvexCollider);

private:
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;
    std::string _path;

    void processMaterial();

    std::map<std::string, LambertMaterial *> nameToLambertMaterial;

    std::vector<GLfloat> scaleVerticesToBoundingBox1x1();

    std::vector<GLfloat> processedVertices;

    Entity *ProcessShape(const tinyobj::shape_t &shape);


};


#endif //WIKENGINE_DESERIALIZER_H
