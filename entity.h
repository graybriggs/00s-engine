#pragma once

#include "./mesh/renderable_mesh.h"
#include "material.h"
#include "texture.h"

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
	//Entity(const RMesh* m, const Material mat, const glm::mat4 model, Texture tex, EntityType et);
	Entity(const RMesh* m, const Material mat, Texture tex, EntityType et);

	void set_material(Material mat);
	void set_model_matrix(glm::mat4 mm);
	void set_texture(GLuint tex);
	void set_viewable_flag(const bool b);
	
	const RMesh* get_mesh() const;
	Material get_material() const;
	glm::mat4 get_model_matrix() const;
	Texture get_texture() const;
	EntityType get_type() const;

	void scale(glm::vec3 factor);
	void translate(glm::vec3 units);
	void rotate(float, glm::vec3 axis);
private:
	const RMesh* mesh;
	// multiple materials that can be changed?
	Material material;
	glm::mat4 model;

	//GLuint texture; // ?

	EntityType entity_type;
	
	Texture texture;
	// Sampler sampler;??

	bool viewable;

};