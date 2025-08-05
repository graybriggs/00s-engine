#include "scene.h"
#include "entity.h"
#include "composite_entity.h"


void Scene::add_entity(Entity* entity) {
    entities.emplace_back(entity);
}

void Scene::add_light(Light* light) {
    lights.emplace_back(light);
}

std::vector<Entity*> Scene::get_entities() const {
    return entities;
}

std::vector<CompositeEntity*> Scene::get_composite_entities() const {
    return composite_entities;
}

std::vector<Light*> Scene::get_lights() const {
    return lights;
}