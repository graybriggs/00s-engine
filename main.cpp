
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
#include "material.h"
#include "renderable_mesh.h"
#include "mesh_cube.h"
#include "mesh_quad.h"
#include "mesh_triangle.h"
#include "scene.h"
#include "shader.h"
#include "timer.h"
#include "video.h"


int main() {

	auto device = makeDevice(config::SCREEN_W, config::SCREEN_H);
	Input in;
	device->set_input(&in);
	auto video = device->getVideoDriver();

	// Ensure we can capture the escape key being pressed below
	//glfwSetInputMode(device->get_window(), GLFW_STICKY_KEYS, GL_TRUE);
	//glfwSetKeyCallback(device->get_window(), key_callback);
	
	////////////////////////////

	video->setup();

	/////////////////////////////

	const auto vs = Shader("vs_texture.vert", ShaderType::VERTEX);
	const auto fs = Shader("fs_texture.frag", ShaderType::FRAGMENT);
	auto material = Material(vs.handle(), fs.handle());
	auto tri_mesh = std::make_unique<RMeshTriangle>();
	//auto cube_mesh = std::make_unique<RMeshCube>();
	//auto quad_mesh = std::make_unique<RMeshQuad>();

	// glm::mat4 mm_e1(1.0f);
	// glm::mat4 mm_e2(1.0f);
	// glm::mat4 mm_e3(1.0f);
	// glm::mat4 mm_e4(1.0f);
	// glm::mat4 mm_e5(1.0f);
	// glm::mat4 mm_e6(1.0f);

	// mm_e1 = glm::translate(mm_e1, glm::vec3(-2.0, -4.0, 0.0));
	// mm_e2 = glm::translate(mm_e2, glm::vec3(0.0, -4.0, 0.0));
	// mm_e3 = glm::translate(mm_e3, glm::vec3(2.0, -4.0, 0.0));
	// mm_e4 = glm::translate(mm_e4, glm::vec3(-2.0, -4.0, -2.0));
	// mm_e5 = glm::translate(mm_e5, glm::vec3(0.0, -4.0, -2.0));
	// mm_e6 = glm::translate(mm_e6, glm::vec3(2.0, -4.0, -2.0));


	// Entity e1(cube_mesh.get(), material, mm_e1);
	// Entity e2(tri_mesh.get(), material, mm_e2);
	// Entity e3(tri_mesh.get(), material, mm_e3);
	// Entity e4(tri_mesh.get(), material, mm_e4);
	// Entity e5(cube_mesh.get(), material, mm_e5);
	// Entity e6(cube_mesh.get(), material, mm_e6);

	Scene scene;
	// scene.entities.emplace_back(&e1);
	// scene.entities.emplace_back(&e2);
	// scene.entities.emplace_back(&e3);
	// scene.entities.emplace_back(&e4);
	// scene.entities.emplace_back(&e5);
	// scene.entities.emplace_back(&e6);

	double x = -32.0;
	double z = -4.0;
	for (int i = 0; i < 1024; ++i) {
		glm::mat4 mm(1.0f);
		mm = glm::translate(mm, glm::vec3(x, -4.0, z));
		Entity* e = new Entity(tri_mesh.get(), material, mm);
		scene.entities.emplace_back(e);
		x += 2.0;
		if (x > 32.0) {
			x = -32.0;
			z -= 2.0;
		}
	}

	auto camera = Camera(
		{0, 0, 15},
		{0, 0, 0},
		{0, 1, 0},
		config::FOV,
		config::SCREEN_W,
		config::SCREEN_H,
		0.1f,
		100.0f
	);
	camera.set_input(&in);


// -------------

	Timer timer;
	timer.start_timer();
	double frame_start = timer.current_time();
	double accumulator = 0.0;
	double delta = 1.0 / config::FPS;

	while (device->run()) {
		
		device->poll_events();

		double current_time = timer.current_time();
		double delta = current_time - frame_start;
		frame_start = current_time;


		if (accumulator > 0.2) {
			accumulator = 0.2;
			// update
		}

		accumulator -= delta;

		camera.update();

		video->begin_scene();


		//glm::mat4 model_matrix = glm::mat4(1.0f);

		//model_matrix_cube = glm::rotate(model_matrix_cube, -0.75f*(float)timer.current_time(), glm::vec3(0.0f, 0.0f, 1.0f));
		//model_matrix_cube= glm::rotate(model_matrix_cube, -0.75f*(float)timer.current_time(), glm::vec3(0.0f, 1.0f, 0.0f));

		

		video->renderer(camera, scene);
		//video->renderer(camera);

		video->end_scene();

		device->window_swap();

	}
	
}