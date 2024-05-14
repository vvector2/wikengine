//
// Created by wiktor on 15.04.24.
//

#include "RigidbodyComponent.h"
#include "Engine.h"
#include "Common.h"
#include "glm/gtx/matrix_decompose.hpp"

RigidbodyComponent::RigidbodyComponent() {
    reactphysics3d::Vector3 position(0.0, 0.0, 0.0);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::Transform transform(position, orientation);
    rigidBody = Engine::physicsWorld->createRigidBody(transform);
    rigidBody->setIsDebugEnabled(true);
    rigidBody->setIsActive(true);
}

RigidbodyComponent::~RigidbodyComponent() {
    Engine::physicsWorld->destroyRigidBody(const_cast<reactphysics3d::RigidBody *>(rigidBody));
}

void RigidbodyComponent::Tranform(glm::mat4 mat) {
    rigidBody->setTransform(MatToReactTransform(mat));

    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(mat, scale, rotation, translation, skew, perspective);

    reactphysics3d::Vector3 scaleReact(scale.x, scale.y, scale.z);

    auto collidor = rigidBody->getCollider(0);
    auto shape = collidor->getCollisionShape();
    auto shapeType = shape->getType();

    switch (shapeType) {
        case reactphysics3d::CollisionShapeType::CAPSULE: {
            auto capsule = dynamic_cast<reactphysics3d::CapsuleShape *>(shape);
            capsule->setHeight(scale.y * capsule->getHeight());
            capsule->setRadius(Max(scale.x, scale.z) * capsule->getRadius());
            break;
        }
        case reactphysics3d::CollisionShapeType::SPHERE: {
            throw std::logic_error("NOT IMPLEMENTED");
        }
        case reactphysics3d::CollisionShapeType::CONVEX_POLYHEDRON: {
            auto boxShape = dynamic_cast<reactphysics3d::BoxShape *>(shape);
            boxShape->setHalfExtents(scaleReact * boxShape->getHalfExtents());
            auto localToBodyTransform = collidor->getLocalToBodyTransform();
            rigidBody->removeCollider(collidor);
            rigidBody->addCollider(boxShape, localToBodyTransform);
            break;
        }
        case reactphysics3d::CollisionShapeType::CONCAVE_SHAPE: {
            auto concaveShape = dynamic_cast<reactphysics3d::ConcaveShape *>(shape);
            concaveShape->setScale(scaleReact);
            break;
        }
    }

}

