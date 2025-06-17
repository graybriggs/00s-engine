
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
	cam_yaw(0.0),
	cam_pitch(0.0) {
	camera_position = position;

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

void Camera::translate(const glm::vec3& v) {

	camera_position += v;
	look_at += v;

	//look_at += std::sin(cam_pitch);
	//look_at += std::cos(cam_yaw);

	glm::vec3 world_up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 cam_right = glm::normalize(glm::cross(world_up, look_at));
	glm::vec cam_up = glm::cross(look_at, cam_right);
	
	//glm::mat4 res = glm::rotate(look_at, yaw, glm::vec3(0.0, 1.0, 0.0));
	
	view = glm::lookAt(camera_position, look_at, cam_up);
}

void Camera::rotate(const float yaw, const float pitch) {

	glm::vec3 direction(
		std::cos(pitch) * std::sin(yaw),
		std::sin(pitch),
		std::cos(pitch) * std::cos(yaw)
	);

	glm::vec3 world_up = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 cam_right = glm::normalize(glm::cross(world_up, look_at));
	glm::vec cam_up = glm::cross(look_at, cam_right);

	view = glm::lookAt(camera_position, camera_position + direction, cam_up);

}

glm::mat4 Camera::get_projection() const {
	return projection;
}

glm::mat4 Camera::get_view() const {
	return view;
}

void Camera::update(double delta) {
	if (input->key[static_cast<int>(Key::KeyPress::W)]) {
		//camera.translate(glm::vec3(5,0,5));
		translate(glm::vec3(0, 0, -0.1));
	}
	if (input->key[static_cast<int>(Key::KeyPress::A)]) {
		//camera.translate(glm::vec3(5,0,5));
		translate(glm::vec3(-0.1, 0, 0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::S)]) {
		//camera.translate(glm::vec3(5,0,5));
		translate(glm::vec3(0, 0, 0.1));
	}		
	if (input->key[static_cast<int>(Key::KeyPress::D)]) {
		//camera.translate(glm::vec3(-5,0,15));
		translate(glm::vec3(0.1, 0, 0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::RIGHT)]) {
		//camera.translate(glm::vec3(-5,0,15));
		//yaw += 0.001;
		yaw += 0.001f;
		rotate(yaw, pitch);
	}
	if (input->key[static_cast<int>(Key::KeyPress::LEFT)]) {
		yaw -= 0.0001;
		rotate(yaw, pitch);
	}
	if (input->key[static_cast<int>(Key::KeyPress::UP)]) {
		pitch += 0.01f;
		rotate(yaw, pitch);
	}
	if (input->key[static_cast<int>(Key::KeyPress::DOWN)]) {
		pitch -= 0.01f;
		rotate(yaw, pitch);
	}

	int xpos, ypos;
	//glfwGetCursorPos(&xpos, &ypos);
	//glfwSetMousePos(config::SCREEN_W / 2, config::SCREEN_H / 2);
	mouse_cursor_pos mouse_pos = input->get_cursor_pos();

	if (input->get_left_mouse_button_state()) {
		printf("x: %f y: %f\n", mouse_pos.xpos, mouse_pos.ypos);
	}


	if (yaw >= 360) yaw = 0.0f;
	if (pitch >= 360) pitch = 0.0f;
	if (yaw < 0) yaw = 360.0f;
	if (pitch < 0) yaw = 360.0f;
}