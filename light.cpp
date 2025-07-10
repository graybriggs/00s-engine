
#include "light.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Light::Light(Material mat, glm::vec3 pos):
    material(mat),
    position(pos) {
}

glm::mat4 Light::get_model_matrix() const {
    return model;
}

glm::vec3 Light::get_position() const {
    return position;
}

glm::vec3 Light::get_color() const {
    return color;
}

Material Light::get_material() const {
    return material;
}

void Light::set_color(const glm::vec3 col) {
    color = col;
}

void Light::translate(glm::vec3 units) {
    model = glm::translate(model, units);
}

void Light::rotate(float angle, glm::vec3 axis) {
    model = glm::rotate(model, angle, axis);
}