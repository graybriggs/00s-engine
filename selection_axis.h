#pragma once

#include "composite_entity.h"

#include <memory>

class SelectionAxis {
public:
    SelectionAxis(const RMesh* m, const Material mat);

    CompositeEntity* get_selection_axis_composite();

    void set_model_matrix(glm::mat4 m);

private:

    std::unique_ptr<Entity> cuboid_x;
    std::unique_ptr<Entity> cuboid_y;
    std::unique_ptr<Entity> cuboid_z;
    std::unique_ptr<Entity> axis_center;

    std::unique_ptr<CompositeEntity> composite_axis;
};