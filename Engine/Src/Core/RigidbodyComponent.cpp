//
// Created by wiktor on 15.04.24.
//

#include "RigidbodyComponent.h"
#include "Engine.h"

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

reactphysics3d::Collider *RigidbodyComponent::AddCollider(reactphysics3d::CollisionShape *shape) {
    return rigidBody->addCollider(shape,
                                  reactphysics3d::Transform::identity());
}

void RigidbodyComponent::SetBodyType(const reactphysics3d::BodyType &value) {
    rigidBody->setType(value);
}
