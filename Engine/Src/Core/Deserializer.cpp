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
#include "LambertMaterial.h"


Entity* ProcessOneItem(const std::vector<tinyobj::index_t> &indices,
                       const std::vector<tinyobj::real_t> &vert,
                       const std::vector<tinyobj::real_t> &normals,
                       const std::vector<tinyobj::real_t> &uv,
                       LambertMaterial &mat
                       ) {

    std::vector<GLfloat> shapeVertices;
    std::vector<GLfloat> shapeUV;
    std::vector<GLfloat> shapeNormals;
    std::vector<GLfloat> shapeColors;


    for (const auto &index: indices) {
        shapeVertices.push_back(vert[index.vertex_index * 3]);
        shapeVertices.push_back(vert[index.vertex_index * 3 + 1]);
        shapeVertices.push_back(vert[index.vertex_index * 3 + 2]);


        
        if (index.texcoord_index != -1) {
            shapeUV.push_back(uv[index.texcoord_index * 2]);
            shapeUV.push_back(uv[index.texcoord_index * 2 + 1]);
        }

        if (index.normal_index != -1) {
            shapeNormals.push_back(normals[index.normal_index * 3]);
            shapeNormals.push_back(normals[index.normal_index * 3 + 1]);
            shapeNormals.push_back(normals[index.normal_index * 3 + 1]);
        }

        shapeColors.push_back(0);
        shapeColors.push_back(0);
        shapeColors.push_back(0);
    }
    auto shapeIndex = GetSequenceOfConsecutiveNumbers(indices.size());

    auto entity = new Entity();
    auto trans = new TransformComponent();
    auto mesh = new MeshComponent(shapeVertices, shapeColors, shapeNormals, shapeUV, shapeIndex);

    entity->AddUpdateComponent(*trans);
    entity->AddUpdateComponent(*mesh);
    entity->AddUpdateComponent(mat);

    return entity;
}

std::map<std::string, LambertMaterial*> ProcessAllMaterials(const std::vector<tinyobj::material_t> &materials, const std::string &path) {
    std::map<std::string, LambertMaterial*> lambMaterial;
    auto folderName = GetFolderFromPath(path);
    for(const auto &mat : materials) {
        auto lambertMaterial = new LambertMaterial();
        auto texture = new Texture( folderName + "/" + mat.diffuse_texname);
        texture->Load();
        lambertMaterial->SetTexture(*texture);
        lambMaterial.insert({mat.name, lambertMaterial});
    }
    return lambMaterial;
}


Entity* ReadFromObj(const std::string &path) {
    std::vector<Entity *> result;

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;

    if (!reader.ParseFromFile(path, reader_config))
        if (!reader.Error().empty())
            throw std::runtime_error("Failed to load obj: " + path);


    if (!reader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning() << std::endl;


    auto &attrib = reader.GetAttrib();
    auto materials = reader.GetMaterials();
    auto vertices = attrib.GetVertices();
    auto &shapes = reader.GetShapes();

    glm::vec3 min;
    glm::vec3 max;
    CalcBox2d(vertices, min, max);


    auto nameToLambertMerial = ProcessAllMaterials(materials, path);
    std::vector<GLfloat> scaledVert = ScaleVerticesToBoundingBox(min, max, vertices);

    for (const auto &shape: shapes) {
        auto materialName = materials[shape.mesh.material_ids[0]].name;
        auto mat = nameToLambertMerial[materialName];
        result.push_back(ProcessOneItem(shape.mesh.indices, scaledVert, attrib.normals, attrib.texcoords, *mat));
    }

    auto fatherEntity = new Entity();
    auto fatherTrans = new TransformComponent();
    fatherEntity->AddUpdateComponent(*fatherTrans);

    for (auto child: result)
        fatherEntity->AddChild(*child);

    return fatherEntity;
}