#pragma once

#include <vector>

#include "composite_entity.h"
#include "entity.h"
#include "light.h"

struct Scene {

    void add_entity(Entity* entity);
    void add_light(Light* light);

    std::vector<Entity*> get_entities() const;
    std::vector<CompositeEntity*> get_composite_entities() const;
    std::vector<Light*> get_lights() const;

    // expand to have filtering; ordering
    std::vector<Entity*> entities;
    std::vector<CompositeEntity*> composite_entities;
    std::vector<Light*> lights;
};