


#include "material.h"
#include "renderable_mesh.h"
#include "mesh_cube.h"
#include "entity.h"
#include "selection_axis.h"

#include <glm/glm.hpp>

#include <memory>

SelectionAxis::SelectionAxis(const RMesh* cube_mesh, const Material material) {
    
    cuboid_x = std::make_unique<Entity>(cube_mesh, material, 0, EntityType::UNTEXTURED_MODEL);
	cuboid_x->set_base_color(EntityBaseColor::RED);
	cuboid_x->scale(glm::vec3(2.5, 0.05, 0.05));
	cuboid_x->translate(glm::vec3(0.5, 0.0, 0.0));
	
	cuboid_y = std::make_unique<Entity>(cube_mesh, material, 0, EntityType::UNTEXTURED_MODEL);
	cuboid_y->set_base_color(EntityBaseColor::GREEN);
	cuboid_y->scale(glm::vec3(0.05, 2.5, 0.05));
	cuboid_y->rotate(glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	cuboid_y->translate(glm::vec3(0.5, 0.0, 0.0));
	
	cuboid_z = std::make_unique<Entity>(cube_mesh, material, 0, EntityType::UNTEXTURED_MODEL);
	cuboid_z->set_base_color(EntityBaseColor::BLUE);
	cuboid_z->scale(glm::vec3(0.05, 0.05, 2.5));
	cuboid_z->rotate(glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
	cuboid_z->translate(glm::vec3(-0.5, 0.0, 0.0));
	
	axis_center = std::make_unique<Entity>(cube_mesh, material, 0, EntityType::UNTEXTURED_MODEL);
	axis_center->set_base_color(EntityBaseColor::WHITE);
	axis_center->scale(glm::vec3(0.5, 0.5, 0.5));

    composite_axis = std::make_unique<CompositeEntity>();

    auto mm = composite_axis->get_model_matrix();
	composite_axis->set_model_matrix(glm::translate(mm, glm::vec3(5.0, 5.0, -5.0)));

    composite_axis->add_child(cuboid_x.get());
	composite_axis->add_child(cuboid_y.get());
	composite_axis->add_child(cuboid_z.get());
	composite_axis->add_child(axis_center.get());
}

CompositeEntity* SelectionAxis::get_selection_axis_composite() {
    return composite_axis.get();
}


void SelectionAxis::set_model_matrix(glm::mat4 m) {
    composite_axis->set_model_matrix(m);
}