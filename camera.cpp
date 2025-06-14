
#include "camera.h"
#include "config.h"
#include "input.h"

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
        float fov,
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
		glm::radians(config::FOV),
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

	view = glm::lookAt(camera_position, look_at, cam_up);

	//view = glm::rotate(view, 180.0, glm::vec3(0.0, 1.0, 0.0));
}

void Camera::rotate(const float yaw, const float pitch) {

	view *= glm::rotate(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	view *= glm::rotate(pitch, glm::vec3(1.0f, 0.0f, 0.0f));

}

glm::mat4 Camera::get_projection() const {
	return projection;
}

glm::mat4 Camera::get_view() const {
	return view;
}

void Camera::update() {
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
	// if (in.key[static_cast<int>(Key::KeyPress::RIGHT)]) {
	// 	//camera.translate(glm::vec3(-5,0,15));
	// 	yaw += 0.01;
	// 	rotate(yaw, pitch);
	// }
	// if (in.key[static_cast<int>(Key::KeyPress::LEFT)]) {
	// 	yaw -= 0.01;
	// 	rotate(yaw, pitch);
	// }
	// if (in.key[static_cast<int>(Key::KeyPress::UP)]) {
	// 	pitch += 0.01f;
	// 	rotate(yaw, pitch);
	// }
	// if (in.key[static_cast<int>(Key::KeyPress::DOWN)]) {
	// 	pitch -= 0.01f;
	// 	rotate(yaw, pitch);
	// }



	
	if (yaw >= 360) yaw = 0.0f;
	if (pitch >= 360) pitch = 0.0f;
	if (yaw < 0) yaw = 360.0f;
	if (pitch < 0) yaw = 360.0f;
}