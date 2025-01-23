#pragma once

#include "mesh.h"
#include "material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Entity {
public:

	Entity(const Mesh* m, Material& mat, glm::mat4& model);

	const Mesh* get_mesh() const;
	Material get_material() const;
	glm::mat4 get_model_matrix() const;

private:
	const Mesh* mesh;
	Material material;
	glm::mat4& model;
};