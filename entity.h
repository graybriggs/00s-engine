#pragma once

#include "./mesh/renderable_mesh.h"
#include "material.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


enum class EntityType {
	UNTEXTURED_MODEL,
	TEXTURED_MODEL,
	LINE
};

enum class EntityBaseColor {
	RED,
	GREEN,
	BLUE,
	WHITE,
	BLACK,
	CYAN,
	PURPLE,
	YELLOW
};

class Entity {
public:

	//Entity(const RMesh* m, const Material mat, const glm::mat4 model, GLuint tex);
	//Entity(const RMesh* m, const Material mat, const glm::mat4 model, Texture tex, EntityType et);
	Entity(const RMesh* m, const Material mat, Texture tex, EntityType et);
	~Entity() = default;

	void set_material(const Material mat);
	void set_model_matrix(const glm::mat4 mm);
	void set_texture(const GLuint tex);
	void set_viewable_flag(const bool b);
	void set_base_position(const glm::vec3 pos);
	void set_base_color(const EntityBaseColor col);
	
	// void add_new_material(Material_* m);
	// Material_* get_new_material();

	const RMesh* get_mesh() const;
	Material get_material() const;
	glm::mat4 get_model_matrix() const;
	glm::vec3 get_3d_coords() const;
	glm::vec3 get_base_position() const;
	int get_base_color() const;
	Texture get_texture() const;
	EntityType get_type() const;
	bool is_viewable() const;

	// behavior
	void scale(glm::vec3 factor);
	void translate(glm::vec3 units);
	void rotate(float, glm::vec3 axis);


	
private:
	const RMesh* mesh;
	// multiple materials that can be changed?
	glm::mat4 model;
	glm::vec3 base_position;

	EntityType entity_type;
	EntityBaseColor entity_base_color;
	
	Texture texture;
	// Sampler sampler;??

	bool viewable;

	Material material;

};