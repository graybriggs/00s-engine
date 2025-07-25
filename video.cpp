
#include <iostream>

#include "camera.h"
#include "config.h"
#include "entity.h"
#include "material.h"
#include "./mesh/renderable_mesh.h"
#include "./mesh/mesh_terrain.h"
#include "terrain_data.h"
#include "scene.h"
#include "video.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>


void VideoDriver::setup() {

	//glDepthFunc(GL_ALWAYS);
	glEnable(GL_DEBUG_OUTPUT);
	glDepthFunc(GL_LESS);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void VideoDriver::begin_scene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void VideoDriver::end_scene() {

}

void VideoDriver::draw_points() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

void VideoDriver::draw_lines() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void VideoDriver::draw_fill() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void VideoDriver::renderer(const Camera& camera, const Scene& scene) {

	// lights
	
	for (const auto light : scene.get_lights()) {

		auto* sh = light->get_material().get_shader("texture");
		sh->use_program();


		glm::vec3 light_pos = light->get_position();
		glm::vec3 light_color = light->get_color();
		sh->set_uniform("light_pos", light_pos);
		sh->set_uniform("light_color", light_color);				
	}
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// models
	
	for (auto ent : scene.entities) {

		auto* sh = ent->get_material().get_shader("texture");
		//auto* sh = ent->get_material().get_shader("color");
		GLuint program = sh->get_program();
		sh->use_program();
		
		glm::mat4 model_matrix = ent->get_model_matrix();
	
		sh->set_uniform("model", model_matrix);
		sh->set_uniform("view", camera.get_view());
		sh->set_uniform("projection", camera.get_projection());
	
		sh->set_texture("tex_sampler0", ent->get_texture(), GL_TEXTURE0);
		
		ent->get_mesh()->bind();
		GLuint idx_count = ent->get_mesh()->get_index_count();
		glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// else if (ent_type == EntityType::LINE) {
		// 	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)0);
		// }
		
		
		ent->get_mesh()->unbind();
	}
}

void VideoDriver::terrain_renderer(const Camera& camera, const RMeshTerrain* rmt, const TerrainRenderData& trd, Material& mat) {

	auto sh = mat.get_shader("color");
	sh->use_program();

	sh->set_uniform("model", glm::mat4(1.0));
	sh->set_uniform("view", camera.get_view());
	sh->set_uniform("projection", camera.get_projection());

	rmt->bind();
	for (int i = 0; i < trd.num_strips; ++i) {
		glDrawElements(GL_TRIANGLE_STRIP, trd.num_verts_per_strip, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * trd.num_verts_per_strip * i));
	}
	rmt->unbind();

}
