
#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"
#include "config.h"
#include "device.h"
#include "entity.h"
#include "input.h"
#include "key.h"
#include "material.h"
#include "./mesh/renderable_mesh.h"
#include "./mesh/mesh_cube.h"
#include "mesh_data.h"
#include "./mesh/mesh_line.h"
#include "./mesh/mesh_model.h"
#include "./mesh/mesh_quad.h"
#include "./mesh/mesh_triangle.h"
#include "model_loader.h"
#include "scene.h"
#include "shader.h"
#include "texture.h"
#include "texture_loader.h"
#include "timer.h"
#include "video.h"


int main() {

	auto device = makeDevice(config::SCREEN_W, config::SCREEN_H);
	auto input = std::make_unique<Input>();
	device->set_input(input.get());
	auto video = device->getVideoDriver();

	////////////////////////////

	video->setup();

	/////////////////////////////

	const auto vs_tex = Shader("./shaders/vs_texture.vert", ShaderType::VERTEX);
	const auto fs_tex = Shader("./shaders/fs_texture.frag", ShaderType::FRAGMENT);
	const auto vs_col = Shader("./shaders/vs_color.vert", ShaderType::VERTEX);
	const auto fs_col = Shader("./shaders/fs_color.frag", ShaderType::FRAGMENT);
	const auto vs_diffuse = Shader("./shaders/vs_diffuse.vert", ShaderType::VERTEX);
	const auto fs_diffuse = Shader("./shaders/fs_diffuse.frag", ShaderType::FRAGMENT);

	const auto texture_material = Material(vs_tex.handle(), fs_tex.handle());
	const auto color_material = Material(vs_col.handle(), fs_col.handle());
	const auto diffuse_material = Material(vs_diffuse.handle(), fs_diffuse.handle());
	const auto tri_mesh = std::make_unique<RMeshTriangle>();
	const auto quad_mesh = std::make_unique<RMeshQuad>();
	const auto cube_mesh = std::make_unique<RMeshCube>();
	const auto line_mesh = std::make_unique<RMeshLine>();
	
	TextureManager tm;
	Texture box_tex(tm.load_texture("thing", "./img/thing.jpg"));
	Texture wall_tex(tm.load_texture("wall", "./img/wall.jpg"));

	//std::cout << "IDs: " << box_tex << ", " << wall_tex << "\n";


	Entity e1(tri_mesh.get(), texture_material, box_tex, EntityType::TEXTURED_MODEL);
	e1.translate(glm::vec3(-5.0, 0.0, -6.0));
	e1.scale(glm::vec3(3,3,3));
	
	Entity e2(tri_mesh.get(), texture_material, box_tex, EntityType::TEXTURED_MODEL);
	e2.translate(glm::vec3(6.0, 2.0, 4.0));
	e2.scale(glm::vec3(4,4,4));

	Entity e3(tri_mesh.get(), texture_material, box_tex, EntityType::TEXTURED_MODEL);
	e3.scale(glm::vec3(5,5,5));
	e3.translate(glm::vec3(4.0, 4.0, 3.0));
	
	Entity e4(tri_mesh.get(), texture_material, box_tex, EntityType::TEXTURED_MODEL);
	e4.translate(glm::vec3(-2.0, 4.0, -2.0));
	Entity e5(tri_mesh.get(), texture_material, box_tex, EntityType::TEXTURED_MODEL);
	e5.translate(glm::vec3(4.0, 4.0, -4.0));
	
	Entity e6(tri_mesh.get(), texture_material, wall_tex, EntityType::TEXTURED_MODEL);
	e6.translate(glm::vec3(-6.0, 2.0, -2.0));
	
	Entity e7(quad_mesh.get(), texture_material, wall_tex, EntityType::TEXTURED_MODEL);
	e7.scale(glm::vec3(10,10,10));
	e7.rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	e7.translate(glm::vec3(0.0, 2.0, 0.0));
	
	Entity e8(line_mesh.get(), color_material, 0, EntityType::LINE);
	e8.scale(glm::vec3(10,1,1));
	e8.rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	Scene scene;
	scene.add(&e1);
	scene.add(&e2);
	scene.add(&e3);
	scene.add(&e4);
	scene.add(&e5);
	scene.add(&e6);
	scene.add(&e7);
	scene.add(&e8);
	
	constexpr int CUBE_MAX = 2048;
	float x = -32.0f;
	float z = -32.0f;
	for (int i = 0; i < CUBE_MAX; ++i) {
		Entity* e = new Entity(cube_mesh.get(), texture_material, wall_tex, EntityType::TEXTURED_MODEL);
		e->translate(glm::vec3(x, -2.0, z));
		scene.entities.emplace_back(e);
		x += 1.0f;
		if (x >= 32.0f) {
			x = -32.0f;
			z += 1.0f;
		}
	}

	MeshData teapot_mesh_data;
	if (!load_obj("./models/sphere.obj", teapot_mesh_data)) {
		std::cout << "Model load failed.\n";
	}
	auto teapot_mesh = std::make_unique<RMeshModel>(teapot_mesh_data);
	Entity ent_teapot(teapot_mesh.get(), diffuse_material, 0, EntityType::UNTEXTURED_MODEL);
	//ent_teapot.rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	ent_teapot.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	ent_teapot.translate(glm::vec3(-2.0f, 2.0f, -1.0f));
	scene.entities.emplace_back(&ent_teapot);

	MeshData suzanne_mesh_data;
	if (!load_obj("./models/suzanne.obj", suzanne_mesh_data)) {
		std::cout << "Model load failed.\n";
	}
	auto suzanne_mesh = std::make_unique<RMeshModel>(suzanne_mesh_data);
	Entity ent_suzanne(suzanne_mesh.get(), diffuse_material, 0, EntityType::UNTEXTURED_MODEL);
	ent_suzanne.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	ent_suzanne.translate(glm::vec3(2.0, 1.0, -3.0));
	scene.entities.emplace_back(&ent_suzanne);


	////////////////

	auto camera = Camera(
		{0, 0, 15}, // pos
		{0, 0, 0}, // lookat
		{0, 1, 0}, // up
		config::SCREEN_W,
		config::SCREEN_H,
		0.1f,
		200.0f
	);
	camera.set_input(input.get());

	glm::vec3 cam_velocity(0.0f, 0.0f, 0.0f);

// -------------

	Timer timer;
	timer.start_timer();
	double frame_start = timer.current_time();
	double accumulator = 0.0;
	double delta = 1.0 / config::FPS;
	

	double last_time = glfwGetTime();
	int frame_count = 0;

	float yaw = 0.0f;
	float pitch = 0.0f;

	//////////////////

	double val = 0.0;

	while (device->run()) {
		
		double current_time = glfwGetTime();
		++frame_count;
		if (current_time - last_time >= 1.0) {
			std::cout << 1000.0 / frame_count << " ms/frame\n";
			frame_count = 0;
			last_time += 1.0;
		}	


		// double current_time = timer.current_time();
		// double delta = current_time - frame_start;
		// frame_start = current_time;
		
		device->poll_events();
		
		if (accumulator > 0.2) {
			accumulator = 0.2;
			// update
		}

		accumulator -= delta;

		mouse_cursor_pos mpos = input->get_cursor_pos();
		//mpos.xpos = input->get_cursor_pos().xpos;
		//mpos.ypos = input->get_cursor_pos().ypos;
		//std::cout << mpos.xpos << " | " << mpos.ypos << "\n";
		float x = float(config::SCREEN_W / 2 - mpos.xpos);
		float y = float(config::SCREEN_H / 2 - mpos.ypos);
		//std::cout << float(config::SCREEN_W / 2) - mpos.xpos << "\n";
		//std::cout << "(" << x << "," << y << ")\n";
		//camera.update_yaw(x);
		//camera.update_pitch(y);

		Entity* t = scene.entities[scene.entities.size()-2];
		//t->translate(glm::vec3(std::sin(val) * 5, 0.0f, 0.0f));
		val += 0.01;
		camera.update(delta);

		
		video->begin_scene();


		//glm::mat4 model_matrix = glm::mat4(1.0f);
		//model_matrix_cube = glm::rotate(model_matrix_cube, -0.75f*(float)timer.current_time(), glm::vec3(0.0f, 0.0f, 1.0f));
		//model_matrix_cube= glm::rotate(model_matrix_cube, -0.75f*(float)timer.current_time(), glm::vec3(0.0f, 1.0f, 0.0f));

		
		video->renderer(camera, scene);

		video->end_scene();

		device->window_swap();

	}

	for (auto e : scene.entities) {
		e->get_mesh()->cleanup();
	}
}