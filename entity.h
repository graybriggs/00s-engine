#pragma once

#include "./mesh/renderable_mesh.h"
#include "material.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


enum class EntityType { UNTEXTURED_MODEL, TEXTURED_MODEL, LIGHT, LINE };

namespace {
	constexpr int UNTEXTURED = 0;
	constexpr int LIGHT = 1;
};

class Entity {
public:

	//Entity(const RMesh* m, const Material mat, const glm::mat4 model, GLuint tex);
	Entity(const RMesh* m, const Material mat, const glm::mat4 model, GLuint tex, EntityType et);

	const RMesh* get_mesh() const;
	Material get_material() const;
	void set_material(Material mat);
	glm::mat4 get_model_matrix() const;
	void set_model_matrix(glm::mat4 mm);
	void set_texture(GLuint tex);
	GLuint get_texture() const;
	EntityType get_type() const;
	void set_viewable_flag(const bool b);

private:
	const RMesh* mesh;
	// multiple materials that can be changed?
	Material material;
	glm::mat4 model;

	GLuint texture; // ?

	EntityType entity_type;
	
	// Texture texture;??
	// Sampler sampler;??

	bool viewable;

};