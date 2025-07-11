#include "scene.h"

void Scene::add_entity(Entity* entity) {
    entities.emplace_back(entity);
}

void Scene::add_light(Light* light) {
    lights.emplace_back(light);
}