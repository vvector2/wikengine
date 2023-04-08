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
#include "Common.h"
#include "BasicColorMaterial.h"

std::vector<Entity*> ReadFromObj(const std::string& path, ShaderProgram &shaderProgramBasictexture) {
    std::vector<Entity*> result;

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "../dedust2/";

    if (!reader.ParseFromFile(path, reader_config))
        if (!reader.Error().empty())
            throw std::runtime_error("Failed to load obj: " + path);


    if (!reader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning() << std::endl;


    auto& attrib = reader.GetAttrib();
    auto materials = reader.GetMaterials();
    auto vertices = attrib.GetVertices();
    auto& shapes = reader.GetShapes();

    glm::vec3 min;
    glm::vec3 max;
    CalcBox2d(vertices, min, max);

    std::vector<GLfloat> arr = {abs(min.x), abs(max.x), abs(min.y), abs(max.y), abs(min.z), abs(max.z) };
    auto scaleFactor = 1 / (*std::max_element(arr.begin(), arr.end()));

    std::vector<GLfloat> scaledVert;
    transform(vertices.begin(), vertices.end(), back_inserter(scaledVert), [scaleFactor](float x) { return x * scaleFactor; } );

    for(auto shape: shapes) {
        auto shapeIndeces = shape.mesh.indices;

        std::vector<GLfloat> shapeVertices;
        std::vector<GLfloat> shapeUV;
        for (auto index: shapeIndeces) {
            shapeVertices.push_back(scaledVert[index.vertex_index * 3]);
            shapeVertices.push_back(scaledVert[index.vertex_index * 3 + 1]);
            shapeVertices.push_back(scaledVert[index.vertex_index * 3 + 2]);

            shapeUV.push_back(attrib.texcoords[index.texcoord_index * 2]);
            shapeUV.push_back(attrib.texcoords[index.texcoord_index * 2 + 1]);
        }

        auto shapeIndex = GetSequenceOfConsecutiveNumbers(shapeIndeces.size());
        auto texturePath = materials[shape.mesh.material_ids[0]].diffuse_texname;

        auto entity = new Entity();
        auto trans = new TransformComponent();
        auto mesh = new MeshComponent(shapeVertices, shapeIndex);
        auto mat = new SimpleTextureMaterial(shaderProgramBasictexture, texturePath, shapeUV);

        entity->AddUpdateComponent(*trans);
        entity->AddUpdateComponent(*mesh);
        entity->AddUpdateComponent(*mat);
        result.push_back(entity);
    }
//
//    auto fatherEntity = new Entity();
//    for(auto child : result)
//        fatherEntity->AddChild(*child);

    return result;
}