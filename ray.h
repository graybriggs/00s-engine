#pragma once

#include "config.h"
#include "input.h"

#include <glm/glm.hpp>

struct NDC {
    float x;
    float y;
};

struct Ray {
    glm::vec4 origin;
    glm::vec4 direction;
};

struct Sphere {
    glm::vec3 center;
    float radius;
};

NDC get_ndc_from_click(const mouse_cursor_pos& mcp);
Ray cast_ray(const mouse_cursor_pos mcp, const glm::mat4& projection, const glm::mat4& view);
bool ray_intersect_sphere(const Ray& ray, const Sphere& sphere);