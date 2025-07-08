
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
	//glEnable(GL_CULL_FACE);
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

		//std::cout << "HANDLE: " << handle << "\n";
		glUseProgram(handle);

		GLuint shader_id_model = glGetUniformLocation(handle, "model");
		glUniformMatrix4fv(shader_id_model, 1, GL_FALSE, glm::value_ptr(model_matrix));
		GLuint shader_id_view = glGetUniformLocation(handle, "view");
		glUniformMatrix4fv(shader_id_view, 1, GL_FALSE, glm::value_ptr(camera.get_view()));
		GLuint shader_id_projection = glGetUniformLocation(handle, "projection");
		glUniformMatrix4fv(shader_id_projection, 1, GL_FALSE, glm::value_ptr(camera.get_projection()));


		GLuint texture_sampler;
		auto texture_id = ent->get_texture();
		ent->get_mesh()->bind();
		
		EntityType ent_type = ent->get_type();
		if (ent_type == EntityType::TEXTURED_MODEL) {
			glBindTexture(GL_TEXTURE_2D, texture_id);
			if (texture_id == 1) {
				texture_sampler = glGetUniformLocation(handle, "tex_sampler0");
				glActiveTexture(GL_TEXTURE0);
			}
			else {
				texture_sampler = glGetUniformLocation(handle, "tex_sampler1");
				glActiveTexture(GL_TEXTURE1);
			}
			//glActiveTexture(GL_TEXTURE0 + texture_id);
			glUniform1i(texture_sampler, GL_TEXTURE0 + texture_id);
			//ent->get_mesh()->bind();
			glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, (void*)0);
		}
		else if (ent_type == EntityType::UNTEXTURED_MODEL) {
			glm::vec3 light_pos(0.0f, 0.0f, -10.0f);
			GLuint shader_light_pos = glGetUniformLocation(handle, "light_pos");
			glUniform3fv(shader_light_pos, 1, glm::value_ptr(light_pos));

			//glUniform3f(handle, 0.0f, 1.0f, 0.0f);
			
			//glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, (void*)0);
			glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, (void*)0);
		}
		else if (ent_type == EntityType::LIGHT) {
			// get light's position and work with that
			// glm::vec3 light_pos(0.0f, 0.0f, 10.0f);
			// GLuint shader_light_pos = glGetUniformLocation(handle, "light_pos");
			// glUniform3fv(handle, 1, glm::value_ptr(light_pos));
		}
		else if (ent_type == EntityType::LINE) {
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)0);
		}
		
		//ent->get_mesh()->bind();
		//glUniform3f(handle, 0.0f, 1.0f, 0.0f);
		//std::cout << "idx count: " << idx_count << "\n";
		
		ent->get_mesh()->unbind();
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
}