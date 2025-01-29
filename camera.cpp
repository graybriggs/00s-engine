
#include "camera.h"
#include "config.h"
#include "input.h"

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
}

void Camera::rotate(const double yaw, const double pitch) {


}

glm::mat4 Camera::get_projection() const {
	return projection;
}

glm::mat4 Camera::get_view() const {
	return view;
}