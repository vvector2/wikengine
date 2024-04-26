//
// Created by wiktor on 15.04.24.
//

#ifndef WIKENGINE_RIGIDBODYCOMPONENT_H
#define WIKENGINE_RIGIDBODYCOMPONENT_H

#include <reactphysics3d/reactphysics3d.h>
#include "IComponent.h"

class RigidbodyComponent : public IComponent {
public:
    ComponentsType GetComponentType() override { return RigidbodyComponentType; }

    RigidbodyComponent();

    ~RigidbodyComponent() override;

    reactphysics3d::RigidBody *GetRigidBody() { return rigidBody; }

private:
    reactphysics3d::RigidBody *rigidBody;

};


#endif //WIKENGINE_RIGIDBODYCOMPONENT_H
