#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Entity {
public:

	virtual ~Entity() = default;

private:
	glm::mat4 model;
	glm::mat4 view;
};