
#include <iostream>

#include "camera.h"
#include "config.h"
#include "entity.h"
#include "material.h"
#include "mesh.h"
#include "video.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>



void VideoDriver::beginScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void VideoDriver::endScene() {

	//glfwSwapBuffers(window);
	//glfwPollEvents(); // MOVE THIS OUT
}


// add instances to the render queue
// instance class looks something likes
// struct Instance {
// ModelAsset* asset;
// glm::mat4 model_transform;
// }
//void VideoDriver::add_mesh(Mesh* mesh) {
void VideoDriver::add_entity(Entity* entity) {
	render_queue.emplace_back(entity);
}

/*
A renderer needs a material and mesh
Renderer renders an entity that contains both
the material and mesh
*/

//void VideoDriver::renderer(const Camera& camera, Mesh* mesh, Material& material, const glm::mat4& model_matrix) {
void VideoDriver::renderer(const Camera& camera) {
	// glm::mat4 view_matrix = glm::lookAt(
	// 	glm::vec3(0, 2, -15), // cam pos
	// 	glm::vec3(0, 0, 0), // camera is looking at (origin)
	// 	glm::vec3(0, 1, 0) // head up direction
	// );

	//glm::mat4 projection_matrix = glm::perspective(glm::radians(config::FOV), config::ASPECT_RATIO, 0.1f, 100.0f);

	for (auto ent : render_queue) {

		// glUseProgram(material.handle());
		// GLuint shader_id_model = glGetUniformLocation(material.handle(), "model");
		// glUniformMatrix4fv(shader_id_model, 1, GL_FALSE, &model_matrix[0][0]);
		// GLuint shader_id_view = glGetUniformLocation(material.handle(), "view");
		// //glUniformMatrix4fv(shader_id_view, 1, GL_FALSE, &view_matrix[0][0]);
		// glUniformMatrix4fv(shader_id_view, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
		// GLuint shader_id_projection = glGetUniformLocation(material.handle(), "projection");
		// //glUniformMatrix4fv(shader_id_projection, 1, GL_FALSE, &projection_matrix[0][0]);
		// glUniformMatrix4fv(shader_id_projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));

		glm::mat4 model_matrix = ent->get_model_matrix();
		GLuint handle = ent->get_material().handle();
		GLuint idx_count = ent->get_mesh()->get_index_count();

		glUseProgram(ent->get_material().handle());
		GLuint shader_id_model = glGetUniformLocation(handle, "model");
		glUniformMatrix4fv(shader_id_model, 1, GL_FALSE, &model_matrix[0][0]);
		GLuint shader_id_view = glGetUniformLocation(handle, "view");
		//glUniformMatrix4fv(shader_id_view, 1, GL_FALSE, &view_matrix[0][0]);
		glUniformMatrix4fv(shader_id_view, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
		GLuint shader_id_projection = glGetUniformLocation(handle, "projection");
		//glUniformMatrix4fv(shader_id_projection, 1, GL_FALSE, &projection_matrix[0][0]);
		glUniformMatrix4fv(shader_id_projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));
		
		ent->get_mesh()->bind();
		glDrawArrays(GL_TRIANGLES, 0, idx_count); // Starting from vertex 0; 3 vertices total -> 1 triangle
		ent->get_mesh()->unbind();
	
	}
}