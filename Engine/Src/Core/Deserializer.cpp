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
#include "RigidbodyComponent.h"
#include "Helpers/BasicCube.h"
#include "Engine.h"


void DeserializerObj::LoadFile(const std::string &path) {
    if (!reader.ParseFromFile(path, reader_config))
        if (!reader.Error().empty())
            throw std::runtime_error("Failed to load obj: " + path);


    if (!reader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning() << std::endl;

    _path = path;
}

Entity *DeserializerObj::CreateEntity(bool loadTexture) {
    processedVertices = scaleVerticesToBoundingBox1x1();

    if (loadTexture)
        processMaterial();


    std::vector<Entity *> result;
    auto &shapes = reader.GetShapes();
    for (const auto &shape: shapes) {
        result.push_back(ProcessShape(shape));
    }

    auto fatherEntity = new Entity();
    auto fatherTrans = new TransformComponent();
    fatherEntity->AddUpdateComponent(*fatherTrans);

    for (auto child: result)
        fatherEntity->AddChild(*child);

    auto rigidBodyCollider = GetCollider();
    fatherEntity->AddUpdateComponent(*rigidBodyCollider);

    return fatherEntity;
}

void DeserializerObj::processMaterial() {
    auto folderName = GetFolderFromPath(_path);
    auto materials = reader.GetMaterials();
    for (const auto &mat: materials) {
        auto lambertMaterial = new LambertMaterial();
        auto texture = new Texture(folderName + "/" + mat.diffuse_texname);
        texture->Load();
        lambertMaterial->SetTexture(*texture);
        nameToLambertMaterial.insert({mat.name, lambertMaterial});
    }
}

std::vector<GLfloat> DeserializerObj::scaleVerticesToBoundingBox1x1() {
    auto vertices = reader.GetAttrib().GetVertices();
    glm::vec3 min;
    glm::vec3 max;
    CalcBox2d(vertices, min, max);
    return ScaleVerticesToBoundingBox(min, max, vertices);
}

std::vector<GLfloat> DeserializerObj::scaleColliderVerticesToBoundingBox1x1() {
    auto colliderVertices = colliderReader.GetAttrib().GetVertices();
    auto vertices = reader.GetAttrib().GetVertices();
    glm::vec3 min;
    glm::vec3 max;
    CalcBox2d(vertices, min, max);
    return ScaleVerticesToBoundingBox(min, max, colliderVertices);
}

Entity *DeserializerObj::ProcessShape(const tinyobj::shape_t &shape) {
    auto &attrib = reader.GetAttrib();
    auto materials = reader.GetMaterials();
    auto normals = attrib.normals;
    auto uv = attrib.texcoords;
    auto vert = processedVertices;

    std::vector<GLfloat> shapeVertices;
    std::vector<GLfloat> shapeUV;
    std::vector<GLfloat> shapeNormals;
    std::vector<GLfloat> shapeColors;


    for (const auto &index: shape.mesh.indices) {
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
            shapeNormals.push_back(normals[index.normal_index * 3 + 2]);
        }

        shapeColors.push_back(0);
        shapeColors.push_back(0);
        shapeColors.push_back(0);
    }
    auto shapeIndex = GetSequenceOfConsecutiveNumbers(shape.mesh.indices.size());

    auto entity = new Entity();
    auto trans = new TransformComponent();
    auto mesh = new MeshComponent(shapeVertices, shapeColors, shapeNormals, shapeUV, shapeIndex);

    auto materialName = materials[shape.mesh.material_ids[0]].name;
    auto mat = nameToLambertMaterial.find(materialName) == nameToLambertMaterial.end() ? new LambertMaterial()
                                                                                       : nameToLambertMaterial[materialName];

    entity->AddUpdateComponent(*trans);
    entity->AddUpdateComponent(*mesh);
    entity->AddUpdateComponent(*mat);

    return entity;
}

void DeserializerObj::LoadCollider(const std::string &path) {
    if (!colliderReader.ParseFromFile(path, colliderReader_config))
        if (!colliderReader.Error().empty())
            throw std::runtime_error("Failed to load obj: " + path);


    if (!colliderReader.Warning().empty())
        std::cout << "TinyObjReader: " << reader.Warning() << std::endl;

    colliderPath = path;
}

RigidbodyComponent *DeserializerObj::GetCollider() {
    auto &shapes = colliderReader.GetShapes();
    auto rigidBody = new RigidbodyComponent();
    auto vert = scaleColliderVerticesToBoundingBox1x1();

    for (const auto &shape: shapes) {
        std::vector<GLfloat> shapeVertices;
        for (const auto &index: shape.mesh.indices) {
            shapeVertices.push_back(vert[index.vertex_index * 3]);
            shapeVertices.push_back(vert[index.vertex_index * 3 + 1]);
            shapeVertices.push_back(vert[index.vertex_index * 3 + 2]);
        }
        auto shapeIndex = GetSequenceOfConsecutiveNumbers(shape.mesh.indices.size());

        const reactphysics3d::TriangleVertexArray triangleVertexArray(shapeVertices.size() / 3,
                                                                      shapeVertices.data(),
                                                                      3 * sizeof(GLfloat),
                                                                      shapeIndex.size() / 3,
                                                                      shapeIndex.data(),
                                                                      3 * sizeof(GLint),
                                                                      reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                      reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
        std::vector<rp3d::Message> messages;
        reactphysics3d::TriangleMesh *triangleMesh = Engine::physicsCommon.createTriangleMesh(triangleVertexArray,
                                                                                              messages);
        for (const rp3d::Message &message: messages)
            std::cout << "Message:" << message.text << std::endl;

        const reactphysics3d::Vector3 scaling(1, 1, 1);
        reactphysics3d::ConcaveMeshShape *concaveMeshShape = Engine::physicsCommon.createConcaveMeshShape(triangleMesh,
                                                                                                          scaling);

        rigidBody->GetRigidBody()->addCollider(concaveMeshShape, reactphysics3d::Transform::identity());
    }


    rigidBody->GetRigidBody()->setType(reactphysics3d::BodyType::STATIC);

    for (auto i = 0; i < rigidBody->GetRigidBody()->getNbColliders(); i++)
        rigidBody->GetRigidBody()->getCollider(i)->getMaterial().setBounciness(0);

    return rigidBody;

}

