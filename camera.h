#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:

    Camera(
        const glm::vec3& position,
        const glm::vec3& look_at,
        const glm::vec3& up,
        float fov,
        float width,
        float height,
        float near_plane,
        float far_plane
    );

    glm::mat4 get_projection() const;
    glm::mat4 get_view() const;

private:

    glm::mat4 projection;
    glm::mat4 view;
};