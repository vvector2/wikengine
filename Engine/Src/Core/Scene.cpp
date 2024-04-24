//
// Created by wiktor on 04.02.23.
//

#include "Scene.h"

void Scene::AddToScene(Entity &entity) {
    head.AddChild(entity);
}

void Scene::RemoveFromScene(sole::uuid id) {
    head.RemoveChild(id);
}

std::vector<Entity *> Scene::GetChilds() {
    return head.GetChilds();
}

void Scene::SetActiveCamera(Entity &entity) {
    camera = &entity;
}

Entity *Scene::GetActiveCamera() {
    return camera;
}

Scene::Scene() {
    head.AddUpdateComponent(tranformComponent);
}
