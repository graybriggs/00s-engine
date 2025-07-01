
#include <iostream>

#include "camera.h"
#include "config.h"
#include "entity.h"
#include "material.h"
#include "renderable_mesh.h"
#include "video.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>


void VideoDriver::setup() {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

void VideoDriver::begin_scene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void VideoDriver::end_scene() {
}



void VideoDriver::renderer(const Camera& camera, const Scene& scene) {


	for (auto ent : scene.entities) {
		glm::mat4 model_matrix = ent->get_model_matrix();
		GLuint handle = ent->get_material().handle();
		GLuint idx_count = ent->get_mesh()->get_index_count();

		glUseProgram(ent->get_material().handle());
		GLuint shader_id_model = glGetUniformLocation(handle, "model");
		glUniformMatrix4fv(shader_id_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
		GLuint shader_id_view = glGetUniformLocation(handle, "view");
		glUniformMatrix4fv(shader_id_view, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
		GLuint shader_id_projection = glGetUniformLocation(handle, "projection");
		glUniformMatrix4fv(shader_id_projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));

		ent->get_mesh()->bind();
		glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, (void*)0);
		//glDrawArrays(GL_TRIANGLES, 0, idx_count); // Starting from vertex 0; 3 vertices total -> 1 triangle
		ent->get_mesh()->unbind();
	}
}