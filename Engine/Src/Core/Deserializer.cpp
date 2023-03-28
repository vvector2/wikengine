//
// Created by wiktor on 20.02.23.
//

#include <iostream>
#include <algorithm>
#include "Deserializer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../../../external/tinyobj/tiny_obj_loader.h"
#include "TransformComponent.h"
#include "MeshComponent.h"


std::vector<Entity*> ReadFromObj(const std::string& path) {
    std::vector<Entity*> result;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path))
        if (!reader.Error().empty())
            throw std::runtime_error("Failed to load obj: " + path);


    if (!reader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning() << std::endl;


    auto& attrib = reader.GetAttrib();
    auto vertices = attrib.GetVertices();
    auto& shapes = reader.GetShapes();

    for(auto shape: shapes) {
        auto shapeIndecesBufferData = shape.mesh.indices;

        std::vector<GLuint> shapeIndexBufferData;

        std::transform(shapeIndecesBufferData.begin(),
                       shapeIndecesBufferData.end(),
                       std::back_inserter(shapeIndexBufferData),
                       [](tinyobj::index_t x) { return x.vertex_index; });

        auto entity = new Entity();
        auto trans = new TransformComponent();
        auto mesh = new MeshComponent(vertices, shapeIndexBufferData);
        entity->AddUpdateComponent(*trans);
        entity->AddUpdateComponent(*mesh);
        result.push_back(entity);
    }

    return result;
}