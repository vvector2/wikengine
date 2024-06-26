//
// Created by wiktor on 17.04.24.
//

#ifndef WIKENGINE_DEBUGCOLLIDER_H
#define WIKENGINE_DEBUGCOLLIDER_H


#include "../ScriptComponent.h"
#include "../MeshComponent.h"
#include "../Engine.h"
#include "../Common.h"
#include "../LambertMaterial.h"
#include "../TransformComponent.h"

class DebugCollider : public ScriptComponent {
public:

    void Setup() override {
        auto lambert = _entity->GetComponent<LambertMaterial>(MaterialComponentType);
        lambert->WireFrame = true;
    }

    void Update(float deltaTime) override {
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> color;
        std::vector<GLfloat> normal;
        std::vector<GLfloat> uv;
        std::vector<GLuint> index;

        auto triangles = Engine::debugRenderer->getTriangles();

        for (const auto &tr: triangles) {
            vertices.push_back(tr.point1.x);
            vertices.push_back(tr.point1.y);
            vertices.push_back(tr.point1.z);

            vertices.push_back(tr.point2.x);
            vertices.push_back(tr.point2.y);
            vertices.push_back(tr.point2.z);

            vertices.push_back(tr.point3.x);
            vertices.push_back(tr.point3.y);
            vertices.push_back(tr.point3.z);

            color.push_back(0);
            color.push_back(1.0f);
            color.push_back(0);

            color.push_back(0);
            color.push_back(1.0f);
            color.push_back(0);

            color.push_back(0);
            color.push_back(1.0f);
            color.push_back(0);
        }

        index = GetSequenceOfConsecutiveNumbers(triangles.size() * 3);

        auto mesh = _entity->GetComponent<MeshComponent>(MeshComponentType);
        if (mesh == nullptr) {
            auto newMesh = new MeshComponent(vertices, color, normal, uv, index);
            _entity->AddUpdateComponent(*newMesh);
        } else {
            mesh->Update(vertices, color, normal, uv, index);
        }
    }

    static Entity *Create() {
        auto entity = new Entity();
        auto mat = new LambertMaterial();
        auto debugColliderScriptComponent = new DebugCollider();
        auto tranform = new TransformComponent();
        entity->AddUpdateComponent(*mat);
        entity->AddUpdateComponent(*debugColliderScriptComponent);
        entity->AddUpdateComponent(*tranform);
        return entity;
    }
};

#endif //WIKENGINE_DEBUGCOLLIDER_H
