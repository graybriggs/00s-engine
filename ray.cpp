
#include "ray.h"

#include "config.h"
#include "input.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

glm::vec4  make_ray(mouse_cursor_pos mcp, glm::mat4 projection, glm::mat4 view) {

    // convert screen coords to NDC

    float ndc_x = (2.0f * mcp.xpos) / config::SCREEN_W - 1.0f;
    float ndc_y = 1.0f - (2.0f * mcp.ypos) / config::SCREEN_H;

    // create clip space position
    auto ray_clip = glm::vec4(ndc_x, ndc_y, -1.0f, 1.0f);

    // convert to view space
    glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;

    // convert to world space
    glm::vec4 ray_world = glm::inverse(view) * ray_eye;
    
    glm::vec4 ray_direction = glm::normalize(glm::vec4(ray_world));

    // The ray origin is the camera position.
    // The ray direction is:
    return ray_direction;
}