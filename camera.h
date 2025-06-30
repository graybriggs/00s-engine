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
    glm::vec3 calculate_direction();
    glm::vec3 calculate_forward();
    glm::vec3 get_world_up();
    void update_yaw(float yaw);
    void update_pitch(float pitch);
    glm::vec3 calculate_camera_right();
    glm::vec3 calculate_camera_up();
    //glm::mat4 calculate_view();
    void update(double delta);
    void print_camera_position();

private:
    Input* input;

	const glm::vec3 WORLD_UP = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 camera_up;
    glm::vec3 camera_right;
    glm::vec3 look_at;
    glm::vec3 camera_position;
    glm::vec3 camera_direction;
    float cam_yaw{};
    float cam_pitch{};
    glm::vec3 camera_speed;
    float camera_fov = 45.0f; // ? 100.0f;
    float mouse_speed = 0.005f;


    glm::mat4 projection;
    glm::mat4 view;
};