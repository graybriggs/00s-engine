
#include "entity.h"
#include "texture.h"

//Entity::Entity(const RMesh* m, const Material mat, const glm::mat4 model, Texture tex, EntityType et):
Entity::Entity(const RMesh* m, const Material mat, Texture tex, EntityType et):
    mesh(m),
    material(mat),
    model(glm::mat4(1.0)),
    texture(tex),
    entity_type(et),
    viewable(true)
{}

const RMesh* Entity::get_mesh() const {
    return mesh;
}

Material Entity::get_material() const {
    return material;
}

void Entity::set_material(Material mat) {
    material = mat;
}

glm::mat4 Entity::get_model_matrix() const {
    return model;
}

void Entity::set_model_matrix(glm::mat4 mm) {
    model = mm;
}

void Entity::set_texture(GLuint tex) {
    texture = tex;
}

Texture Entity::get_texture() const {
    return texture;
}

EntityType Entity::get_type() const {
    return entity_type;
}

void Entity::set_viewable_flag(const bool b) {
    viewable = b;
}

void Entity::scale(glm::vec3 factor) {
    model = glm::scale(model, factor);
}

void Entity::translate(glm::vec3 units) {
    model = glm::translate(model, units);
}

void Entity::rotate(float angle, glm::vec3 axis) {
    model = glm::rotate(model, angle, axis);
}