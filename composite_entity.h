#pragma once

#include "entity.h"
#include "standard_entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <initializer_list>
#include <vector>



//class CompositeEntity : public Entity {

class CompositeEntity {
public:

    CompositeEntity(std::initializer_list<Entity*> values);
    //CompositeEntity(const RMesh* m, const Material mat, Texture tex, EntityType et);
    //~CompositeEntity() = default;

    void add_child(Entity* child);
    const std::vector<Entity*>& get_children() const;
    // const glm::mat4& get_model_matrix() const override;

    const std::vector<Entity*>& get_children() const;
    const glm::mat4& get_model_matrix() const;

    // void scale(glm::vec3 factor);
    // void translate(glm::vec3 units);
    // void rotate(float angle, glm::vec3 axis);


private:
    glm::mat4 model;
    std::vector<Entity*> children;
};