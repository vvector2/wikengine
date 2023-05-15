#include "Entity.h"
#include "Common.h"

Entity::Entity() {
    id = GenerateUUID();
}

std::vector<Entity *> Entity::GetChilds() {
    std::vector<Entity *> result;
    for (const auto &s: childs)
        result.push_back(s.second);
    return result;
}

void Entity::AddChild(Entity &entity) {
    childs[entity.ID().str()] = &entity;
}

void Entity::RemoveChild(sole::uuid _id) {
    childs.erase(_id.str());
}

sole::uuid Entity::ID() const {
    return id;
}

Entity::~Entity() {
    for (const auto &child: childs)
        delete child.second;
    for (const auto &component: components)
        delete component.second;
}
