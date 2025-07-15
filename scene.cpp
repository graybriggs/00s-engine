#include "scene.h"

void Scene::add_entity(Entity* entity) {
    entities.emplace_back(entity);
}

void Scene::add_light(Light* light) {
    lights.emplace_back(light);
}

std::vector<Entity*> Scene::get_entities() {
    return entities;
}
std::vector<Light*> Scene::get_lights() {
    return lights;
}