#include "scene.h"

void Scene::add(Entity* ent) {
    entities.emplace_back(ent);
}