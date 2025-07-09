#pragma once

#include <vector>

#include "entity.h"

struct Scene {

    void add(Entity* ent);

    // expand to have filtering; ordering
    std::vector<Entity*> entities;
};