
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
	cam_yaw(0.0f) {
	

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

glm::vec3 Camera::calculate_forward() {
	float z = sin(cam_yaw);
	float x = cos(cam_yaw); 
	//return glm::vec3(x, 0, z);
	return calculate_direction();
}


void Camera::update_yaw(float yaw) {
	cam_yaw += yaw;
	//camera_direction = calculate_direction();
	camera_direction = glm::normalize(calculate_forward());
	view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
}

void Camera::update_pitch(float pitch) {
	//cam_pitch += pitch;
	cam_pitch += pitch;
	//camera_direction = calculate_direction();
	camera_direction = glm::normalize(calculate_forward());
	view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
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
	
	//print_camera_position();


	if (input->key[static_cast<int>(Key::KeyPress::W)]) {
		//glm::vec3 movement_velocity(0.0f, 0.0f, 1.0f);
		//translate(glm::normalize(movement_velocity));

		//camera_direction -= glm::vec3(0,0,1) * velocity;
		
		camera_position += calculate_forward() * camera_velocity;
		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::S)]) {
		
		//camera_position += glm::vec3(0,0,1) * velocity;
		
		camera_position -= calculate_forward() * camera_velocity;
		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}		
	if (input->key[static_cast<int>(Key::KeyPress::A)]) {

		camera_direction = glm::normalize(calculate_forward()); // temp: this stops nan bug

		glm::vec3 right = glm::normalize(glm::cross(camera_direction, glm::vec3(0,1,0)));
		camera_position -= right * camera_velocity;

		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::D)]) {

		camera_direction = glm::normalize(calculate_forward()); // temp: this stops nan bug

		glm::vec3 right = glm::normalize(glm::cross(camera_direction, glm::vec3(0,1,0)));
		camera_position += right * camera_velocity;

		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::RIGHT)]) {
		cam_yaw -= 0.03f;
		
		camera_direction = glm::normalize(calculate_forward());
		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::LEFT)]) {
		cam_yaw += 0.03f;

		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::UP)]) {
		cam_pitch -= 0.01f;

		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}
	if (input->key[static_cast<int>(Key::KeyPress::DOWN)]) {
		cam_pitch += 0.01f;

		camera_direction = glm::normalize(calculate_forward());

		view = glm::lookAt(camera_position, camera_position + camera_direction, glm::vec3(0,1,0));
	}

	// int xpos, ypos;
	//glfwGetCursorPos(&xpos, &ypos);
	//glfwSetMousePos(config::SCREEN_W / 2, config::SCREEN_H / 2);
	
	//mouse_cursor_pos mouse_pos = input->get_cursor_pos();

	// if (input->get_left_mouse_button_state()) {
	// 	printf("x: %f y: %f\n", mouse_pos.xpos, mouse_pos.ypos);
	// }


	// if (cam_yaw <= 0.0f) cam_yaw = 360.0f;
	// if (cam_yaw > 360.0f) cam_yaw = 0.0f;
	// if (cam_pitch <= 0.0f) cam_pitch = 360.0f;
	// if (cam_pitch > 360.0f) cam_pitch = 0.0f;
}

void Camera::print_camera_position() {
	std::cout << camera_position.x << "," << camera_position.z << std::endl;
}