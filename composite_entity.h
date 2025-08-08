#pragma once

#include "entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>


class CompositeEntity {
public:
    
    CompositeEntity();

    void set_model_matrix(const glm::mat4& m);

    void add_child(Entity* child);
    const std::vector<Entity*>& get_children() const;

    const glm::mat4& get_model_matrix() const;

    // behavior
    void scale(glm::vec3 factor);
    void translate(glm::vec3 units);
    void rotate(float angle, glm::vec3 axis);


private:
    glm::mat4 model;
    std::vector<Entity*> children;
};