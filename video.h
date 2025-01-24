#pragma once

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"
#include "mesh.h"

class Entity;
class Material;
class MeshTriangle;

class VideoDriver {
public:

	void setup();

	void beginScene();
	void endScene();

	// this will be Instance
	//void add_mesh(Mesh* mesh);
	void add_entity(Entity* entity);

	//void renderer(const Camera& camera, Mesh* mesh, Material& material, const glm::mat4& model_matrix);
	void renderer(const Camera& camera);

private:

	//std::vector<Mesh*> mesh_list;
	std::vector<Entity*> render_queue;
};

