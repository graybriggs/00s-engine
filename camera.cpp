
#include "camera.h"
#include "config.h"
#include "input.h"
#include "key.h"

#include <cmath>
#include <cstdio>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


Camera::Camera(
        const glm::vec3& position,
        const glm::vec3& look_at,
        const glm::vec3& up,
        float width,
        float height,
        float near_plane,
        float far_plane
	):
	camera_position(position) {

	view = glm::lookAt(
		camera_position,
		look_at,
		up
		// glm::vec3(0, 0, 5), // cam pos
		// glm::vec3(0, 0, 0), // camera is looking at (origin)
		// glm::vec3(0, 1, 0) // head up direction
	);

    projection = glm::perspective(
		glm::radians(camera_fov),
		config::ASPECT_RATIO, // width / height 
		near_plane,
		far_plane
		//0.1f,
		//100.0f
	);

}


void Camera::set_input(Input* in) {
	input = in;
}

glm::vec3 Camera::create_direction(const float yaw, const float pitch) {

	auto y = glm::radians(yaw);
	auto p = glm::radians(pitch);

	return glm::normalize(glm::vec3(
		std::cos(p) * std::sin(y),
		std::sin(p),
		std::cos(p) * std::cos(y)
	));
}

glm::mat4 Camera::calculate_view() {
	
	glm::vec3 direction = create_direction(cam_yaw, cam_pitch);
	
	camera_right = glm::normalize(glm::cross(world_up, direction));
	camera_up = glm::cross(camera_right, direction);
	
	return glm::lookAt(camera_position, camera_position + direction, camera_up);
}

void Camera::translate(const glm::vec3& v) {

	//view = calculate_view();
	
	glm::vec3 direction = create_direction(cam_yaw, cam_pitch); // look_at
	
	camera_right = glm::normalize(glm::cross(world_up, direction));
	camera_up = glm::cross(camera_right, direction);
	
	camera_position += v;
	view = glm::lookAt(camera_position, camera_position + direction, camera_up);
}

glm::mat4 Camera::get_projection() const {
	return projection;
}

glm::mat4 Camera::get_view() const {
	return view;
}

void Camera::update(double delta) {
	if (input->key[static_cast<int>(Key::KeyPress::W)]) {
		glm::vec3 movement_velocity(0.0f, 0.0f, 0.5f);
		translate(movement_velocity);
	}
	if (input->key[static_cast<int>(Key::KeyPress::S)]) {
		translate(glm::vec3(0, 0, -0.5f));
	}		
	if (input->key[static_cast<int>(Key::KeyPress::A)]) {
		translate(glm::vec3(0.5f, 0, 0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::D)]) {
		translate(glm::vec3(-0.5f, 0, 0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::RIGHT)]) {
		cam_yaw -= 0.2f;
		view = calculate_view();
	}
	if (input->key[static_cast<int>(Key::KeyPress::LEFT)]) {
		cam_yaw += 0.2;
		view = calculate_view();
	}
	if (input->key[static_cast<int>(Key::KeyPress::UP)]) {
		cam_pitch -= 0.2f;
		view = calculate_view();
	}
	if (input->key[static_cast<int>(Key::KeyPress::DOWN)]) {
		cam_pitch += 0.2f;
		view = calculate_view();
	}

	int xpos, ypos;
	//glfwGetCursorPos(&xpos, &ypos);
	//glfwSetMousePos(config::SCREEN_W / 2, config::SCREEN_H / 2);
	
	//mouse_cursor_pos mouse_pos = input->get_cursor_pos();

	// if (input->get_left_mouse_button_state()) {
	// 	printf("x: %f y: %f\n", mouse_pos.xpos, mouse_pos.ypos);
	// }


	if (cam_yaw <= 0) cam_yaw = 360.0f;
	if (cam_yaw > 360) cam_yaw = 0.0f;
	if (cam_pitch <= 0) cam_pitch = 360.0f;
	if (cam_pitch > 360) cam_pitch = 0.0f;
}