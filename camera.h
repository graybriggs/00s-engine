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
        float width,
        float height,
        float near_plane,
        float far_plane
    );

    glm::mat4 get_projection() const;
    glm::mat4 get_view() const;

    void set_input(Input* in);
    void translate(const glm::vec3& v);
    glm::vec3 create_direction(const float yaw, const float pitch);
    glm::mat4 calculate_view();
    void update(double delta);

private:
    Input* input;

	glm::vec3 world_up = glm::normalize(glm::vec3(0.0, -1.0, 0.0));
    glm::vec3 camera_up;
    glm::vec3 camera_right;
    glm::vec3 look_at;
    glm::vec3 camera_position;
    double cam_yaw;
    double cam_pitch;
    
    float camera_fov = 45.0f; // ? 100.0f;
    float mouse_speed = 0.005f;


    glm::mat4 projection;
    glm::mat4 view;
};