
#include "camera.h"
#include "config.h"
#include "input.h"
#include "key.h"

#include <cmath>
#include <cstdio>
#include <iostream>

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
	camera_position(glm::normalize(position)),
	camera_direction(glm::vec3(0,0,0)),
	cam_pitch(0.0f),
	cam_yaw(0.0f),
	camera_velocity(0.7f) {
	

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

// calculates "look at" vector
glm::vec3 Camera::calculate_direction() {
	
	auto y = cam_yaw;
	auto p = cam_pitch;

	return glm::normalize(
		glm::vec3(
			glm::cos(p) * glm::sin(y),
			glm::sin(p),
			glm::cos(p) * glm::cos(y)
		)
	);
}

glm::vec3 Camera::get_camera_position() {
	return camera_position;
}

void Camera::update_yaw(float yaw) {
	cam_yaw += yaw;
	camera_direction = calculate_direction();
	view = glm::lookAt(camera_position, camera_position + camera_direction, calculate_camera_up());
}

void Camera::update_pitch(float pitch) {
	cam_pitch += pitch;
	camera_direction = calculate_direction();
	view = glm::lookAt(camera_position, camera_position + camera_direction, calculate_camera_up());
}

glm::vec3 Camera::get_world_up() {
	return glm::normalize(WORLD_UP);
}

glm::vec3 Camera::calculate_camera_right() {
	return glm::normalize(glm::cross(camera_direction, WORLD_UP));
}

glm::vec3 Camera::calculate_camera_up() {
	glm::vec3 cam_right = calculate_camera_right();
	return glm::normalize(glm::cross(cam_right, camera_direction));
}

void Camera::set_velocity(const float vel) {
	camera_velocity = vel;
}

void Camera::translate(const glm::vec3& vec) {

	camera_position += vec;
	camera_direction = calculate_direction(); // look_at

	print_camera_position();
	
	camera_right = glm::normalize(glm::cross(camera_direction, WORLD_UP));
	camera_up = glm::normalize(glm::cross(camera_right, camera_direction));
	
	view = glm::lookAt(camera_position, camera_position + camera_direction, camera_up);
}

glm::mat4 Camera::get_projection() const {
	return projection;
}

glm::mat4 Camera::get_view() const {
	return view;
}

void Camera::update(double delta) {
	
	if (input->key[Key_W]) {
		
		camera_position += calculate_direction() * camera_velocity;
		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::S)]) {
		
		camera_position -= calculate_direction() * camera_velocity;
		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}		
	if (input->key[Key_A]) {

		camera_direction = calculate_direction(); // temp: this stops nan bug

		glm::vec3 right = glm::normalize(glm::cross(camera_direction, glm::vec3(0,1,0)));
		camera_position -= right * camera_velocity;

		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[Key_D]) {

		camera_direction = calculate_direction(); // temp: this stops nan bug

		glm::vec3 right = glm::normalize(glm::cross(camera_direction, glm::vec3(0,1,0)));
		camera_position += right * camera_velocity;

		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[Key_RIGHT]) {
		cam_yaw -= 0.03f;
		
		camera_direction = calculate_direction();
		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::LEFT)]) {
		cam_yaw += 0.03f;

		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[Key_UP]) {
		cam_pitch -= 0.01f;

		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[Key_DOWN]) {
		cam_pitch += 0.01f;

		camera_direction = calculate_direction();

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
}

void Camera::print_camera_position() {
	std::cout << camera_position.x << "," << camera_position.z << std::endl;
}