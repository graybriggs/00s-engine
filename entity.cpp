
#include "entity.h"

Entity::Entity(const RMesh* m, const Material mat, const glm::mat4 model, GLuint tex, EntityType et):
    mesh(m),
    material(mat),
    model(model),
    texture(tex),
    entity_type(et)
{}

const RMesh* Entity::get_mesh() const {
    return mesh;
}

Material Entity::get_material() const {
    return material;
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

GLuint Entity::get_texture() const {
    return texture;
}

EntityType Entity::get_type() const {
    return entity_type;
}