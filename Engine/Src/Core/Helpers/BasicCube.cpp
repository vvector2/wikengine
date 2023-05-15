//
// Created by wiktor on 11.05.23.
//
#include "BasicCube.h"
#include "../MeshComponent.h"
#include "../LambertMaterial.h"


std::vector<GLfloat> vertexCube = {
        //back
        1.f, 1.f, 1.f,
        -1.f, 1.f, 1.f,
        1.f, -1.f, 1.f,

        //back 2
        -1.f, -1.f, 1.f,
        -1.f, 1.f, 1.f,
        1.f, -1.f, 1.f,

        //front 1
        1.f, 1.f, -1.f,
        -1.f, 1.f, -1.f,
        1.f, -1.f, -1.f,

        //front 2
        -1.f, -1.f, -1.f,
        -1.f, 1.f, -1.f,
        1.f, -1.f, -1.f,

        //top 1
        1.f, 1.f, 1.f,
        -1.f, 1.f, 1.f,
        1.f, 1.f, -1.f,

        //top 2
        -1.f, 1.f, 1.f,
        1.f, 1.f, -1.f,
        -1.f, 1.f, -1.f,

        //bottom 1
        1.f, -1.f, 1.f,
        -1.f, -1.f, 1.f,
        1.f, -1.f, -1.f,

        //bottom 2
        -1.f, -1.f, 1.f,
        1.f, -1.f, -1.f,
        -1.f, -1.f, -1.f,

        //left 1
        -1.f, -1.f, 1.f,
        -1.f, -1.f, -1.f,
        -1.f, 1.f, -1.f,

        //left 2
        -1.f, 1.f, 1.f,
        -1.f, 1.f, -1.f,
        -1.f, -1.f, 1.f,

        //right 1
        1.f, -1.f, 1.f,
        1.f, -1.f, -1.f,
        1.f, 1.f, -1.f,

        //right 2
        1.f, 1.f, 1.f,
        1.f, 1.f, -1.f,
        1.f, -1.f, 1.f,
};


std::vector<GLfloat> normalCube = {
        //back 0.0f, 0.0f, 1.f,
        0.0f, 0.0f, 1.f,
        0.0f, 0.0f, 1.f,
        0.0f, 0.0f, 1.f,

        //back 2
        0.0f, 0.0f, 1.f,
        0.0f, 0.0f, 1.f,
        0.0f, 0.0f, 1.f,

        //front 1
        0.0f, 0.0f, -1.f,
        0.0f, 0.0f, -1.f,
        0.0f, 0.0f, -1.f,

        //front 2
        0.0f, 0.0f, -1.f,
        0.0f, 0.0f, -1.f,
        0.0f, 0.0f, -1.f,

        //top
        0.0f, 1.0f, 0.f,
        0.0f, 1.0f, 0.f,
        0.0f, 1.0f, 0.f,

        //top 2
        0.0f, 1.0f, 0.f,
        0.0f, 1.0f, 0.f,
        0.0f, 1.0f, 0.f,

        //bottom 1
        0.0f, -1.0f, 0.f,
        0.0f, -1.0f, 0.f,
        0.0f, -1.0f, 0.f,

        //bottom 2
        0.0f, -1.0f, 0.f,
        0.0f, -1.0f, 0.f,
        0.0f, -1.0f, 0.f,

        //left 1
        -1.0f, 0.0f, 0.f,
        -1.0f, 0.0f, 0.f,
        -1.0f, 0.0f, 0.f,

        //left 2
        -1.0f, 0.0f, 0.f,
        -1.0f, 0.0f, 0.f,
        -1.0f, 0.0f, 0.f,

        //right 1
        1.0f, 0.0f, 0.f,
        1.0f, 0.0f, 0.f,
        1.0f, 0.0f, 0.f,

        //right 2
        1.0f, 0.0f, 0.f,
        1.0f, 0.0f, 0.f,
        1.0f, 0.0f, 0.f,
};


std::vector<GLfloat> colorCube = {
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,

        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
        225.f / 255.f, 0.f, 1.f,
};

std::vector<GLuint> indexCube = {
        0, 1, 2, 3, 4, 5,
        6, 7, 8, 9, 10, 11,
        12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29,
        30, 31, 32, 33, 34, 35
};

std::vector<GLfloat> uvCube = {
        1.f, 1.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        1.f, 1.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,

        0.f, 0.f,
        0.f, 1.f,
        1.f, 0.f,
};


Entity *CreateBasicCube() {
    auto transformComponent = new TransformComponent();
    auto mesh = new MeshComponent(vertexCube, colorCube, normalCube, uvCube, indexCube);
    auto lambertMaterial = new LambertMaterial();

    auto entity = new Entity();
    auto cubeScript = new CubeScript(*entity);
    entity->AddUpdateComponent(*transformComponent);
    entity->AddUpdateComponent(*mesh);
    entity->AddUpdateComponent(*lambertMaterial);
    entity->AddUpdateComponent(*cubeScript);

    return entity;
}

CubeScript::CubeScript(Entity &entity) : ScriptComponent(entity) {

}
