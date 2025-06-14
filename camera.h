#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Input;

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

    void set_input(Input* in);
    void translate(const glm::vec3& v);
    void rotate(const float yaw, const float pitch);

    void update();

private:
    Input* input;

    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 look_at;
    glm::vec3 camera_position;
    double cam_yaw;
    double cam_pitch;
    float yaw = 0.0f;
	float pitch = 0.0f;

    glm::mat4 projection;
    glm::mat4 view;
};