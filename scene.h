#pragma once

#include <vector>

#include "entity.h"

struct Scene {
    // expand to have filtering; ordering
    std::vector<Entity*> entities;
};