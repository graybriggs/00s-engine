
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

glm::vec3 Entity::get_base_position() const {
    return base_position;
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

int Entity::get_base_color() const {
    if (entity_base_color == EntityBaseColor::RED)
        return 0;
    if (entity_base_color == EntityBaseColor::GREEN)
        return 1;
    if (entity_base_color == EntityBaseColor::BLUE)
        return 2;
    if (entity_base_color == EntityBaseColor::WHITE)
        return 3;

    return -1;
}

bool Entity::is_viewable() const {
    return viewable;
}

void Entity::set_viewable_flag(const bool b) {
    viewable = b;
}

void Entity::set_base_position(const glm::vec3 pos) {
    base_position = pos;
}

void Entity::set_base_color(const EntityBaseColor col) {
    entity_base_color = col;
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


// void Entity::add_new_material(Material_* m) {
//     mat = m;
// }

// Material_* Entity::get_new_material() {
//     return mat;
// }