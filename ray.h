#pragma once

#include "config.h"
#include "input.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

glm::vec4 make_ray(mouse_cursor_pos mcp, glm::mat4 projection, glm::mat4 view);

bool ray_intersect_sphere(glm::vec3 ray_origin, glm::vec3 ray_dir, glm::vec3 sphere_center, float sphere_radius);