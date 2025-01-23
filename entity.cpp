
#include "entity.h"

Entity::Entity(const Mesh* m, Material& mat, glm::mat4& model):
    mesh(m),
    material(mat),
    model(model)
{}

const Mesh* Entity::get_mesh() const {
    return mesh;
}

Material Entity::get_material() const {
    return material;
}

glm::mat4 Entity::get_model_matrix() const {
    return model;
}