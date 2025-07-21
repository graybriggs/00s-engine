
#include <iostream>

#include "camera.h"
#include "config.h"
#include "entity.h"
#include "material.h"
#include "./mesh/renderable_mesh.h"
#include "scene.h"
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

	// lights
	
	for (const auto light : scene.get_lights()) {

		//shader.use_program("normals");
		//GLuint lp = shader.get_uniform("light_pos");
		//GLuint lc = shader.get_uniform("light_color");

		//GLuint handle = light->get_material().handle();
		GLuint handle = light->get_material().get_shader("texture")->get_program();
		glUseProgram(handle);

		//glm::vec3 light_pos(10.0f, 8.0f, -10.0f);
		glm::vec3 light_pos = light->get_position();
		glm::vec3 light_color = light->get_color();
		GLuint shader_light_pos = glGetUniformLocation(handle, "light_pos");
		GLuint shader_light_color = glGetUniformLocation(handle, "light_color");
		glUniform3fv(shader_light_pos, 1, glm::value_ptr(light_pos));
		glUniform3fv(shader_light_color, 1, glm::value_ptr(light_color));
		
	}
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// models
	
	for (auto ent : scene.entities) {

		auto* sh = ent->get_material().get_shader("texture");
		//GLuint program = sh->get_program();
		sh->use_program();
		
		glm::mat4 model_matrix = ent->get_model_matrix();
	
		sh->set_uniform("model", model_matrix);
		sh->set_uniform("view", camera.get_view());
		sh->set_uniform("projection", camera.get_projection());
	
		sh->set_texture("tex_sampler0", ent->get_texture(), GL_TEXTURE0);
		
		ent->get_mesh()->bind();
		GLuint idx_count = ent->get_mesh()->get_index_count();
		glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, (void*)0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// else if (ent_type == EntityType::LINE) {
		// 	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)0);
		// }
		
		
		ent->get_mesh()->unbind();
	}
}