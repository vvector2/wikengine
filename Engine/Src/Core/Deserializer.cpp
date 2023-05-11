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


Entity* ProcessOneItem(const std::vector<tinyobj::index_t>& indices,
                       const std::vector<tinyobj::real_t>& vert,
                       const std::vector<tinyobj::real_t>& uv,
                       const tinyobj::material_t& materials,
                       const ShaderProgram& shaderProgram) {

    std::vector<GLfloat> shapeVertices;
    std::vector<GLfloat> shapeUV;
    for (auto index: indices) {
        shapeVertices.push_back(vert[index.vertex_index * 3]);
        shapeVertices.push_back(vert[index.vertex_index * 3 + 1]);
        shapeVertices.push_back(vert[index.vertex_index * 3 + 2]);

//        shapeUV.push_back(uv[index.texcoord_index * 2]);
//        shapeUV.push_back(uv[index.texcoord_index * 2 + 1]);
    }

    auto shapeIndex = GetSequenceOfConsecutiveNumbers(indices.size());
    //auto texturePath = materials.diffuse_texname;

    auto entity = new Entity();
    auto trans = new TransformComponent();
    auto mesh = new MeshComponent(shapeVertices, shapeIndex);
    auto mat = new BasicColorMaterial(glm::vec3(0.5, 0.5, 0.5), shaderProgram);

    entity->AddUpdateComponent(*trans);
    entity->AddUpdateComponent(*mesh);
    entity->AddUpdateComponent(*mat);

    return entity;
}


Entity* ReadFromObj(const std::string& path, ShaderProgram &shaderProgramBasictexture) {
    std::vector<Entity*> result;

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "../";

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

    std::vector<GLfloat> scaledVert = ScaleVerticesToBoundingBox(min, max, vertices);

    for(auto shape: shapes) {
        result.push_back(
                ProcessOneItem(shape.mesh.indices,
                               scaledVert,
                               attrib.texcoords,
                               materials[shape.mesh.material_ids[0]],
                               shaderProgramBasictexture)
                );
    }

    auto fatherEntity = new Entity();
    auto fatherTrans = new TransformComponent();
    fatherEntity->AddUpdateComponent(*fatherTrans);

    for(auto child : result)
        fatherEntity->AddChild(*child);

    return fatherEntity;
}