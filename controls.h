#pragma once

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "config.h"

void orientation(float deltaTime) {

	// position
	glm::vec3 position = glm::vec3(0, 0, 5);
	// horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;


	int xpos = config::SCREEN_W / 2;
	int ypos = config::SCREEN_H / 2;
	//glfwGetMousePos(&xpos, &ypos);
	// Reset mouse position for next frame
	//glfwSetMousePos(1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(config::SCREEN_W / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(config::SCREEN_H / 2 - ypos);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
}