
#include "composite_entity.h"
#include "entity.h"


// CompositeEntity::CompositeEntity(const RMesh* m, const Material mat, Texture tex, EntityType et):
//     Entity(m, mat, tex, et)
//     {}

CompositeEntity::CompositeEntity(std::initializer_list<Entity*> values):
    children(values)
{
}

void CompositeEntity::add_child(Entity* child) {
    children.push_back(child);
}

const std::vector<Entity*>& CompositeEntity::get_children() const {
    return children;
}


const glm::mat4& CompositeEntity::get_model_matrix() const {
    return model;
}


// void CompositeEntity::scale(glm::vec3 factor) {
//     model = glm::scale(model, factor);
// }

// void CompositeEntity::translate(glm::vec3 units) {
//     model = glm::translate(model, units);
// }

// void CompositeEntity::rotate(float angle, glm::vec3 axis) {
//     model = glm::rotate(model, angle, axis);
// }