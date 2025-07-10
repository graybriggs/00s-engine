#pragma once

#include "material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Light {
public:
    Light() = default;
    Light(Material mat, glm::vec3 pos);
    
    glm::mat4 get_model_matrix() const;
    glm::vec3 get_position() const;
    glm::vec3 get_color() const;
    Material get_material() const;

    void set_color(const glm::vec3 col);

    void translate(glm::vec3 units);
	void rotate(float, glm::vec3 axis);
private:
    glm::mat4 model;
    glm::vec3 position;
    glm::vec3 color;
    Material material;
    bool viewable;
    // point light?
    // direction?
};