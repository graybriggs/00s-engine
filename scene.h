#pragma once

#include <vector>

#include "entity.h"
#include "light.h"

struct Scene {

    void add_entity(Entity* entity);
    void add_light(Light* light);

    // expand to have filtering; ordering
    std::vector<Entity*> entities;
    std::vector<Light*> lights;
};