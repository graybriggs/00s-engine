
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
#include "light.h"
#include "material.h"
#include "./mesh/renderable_mesh.h"
#include "./mesh/mesh_cube.h"
#include "mesh_data.h"
#include "./mesh/mesh_line.h"
#include "./mesh/mesh_model.h"
#include "./mesh/mesh_quad.h"
#include "./mesh/mesh_triangle.h"
#include "model_loader.h"
#include "ray.h"
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
	 Shader color_shader("./shaders/vs_color.vert", "./shaders/fs_color.frag");
	 Shader diffuse_shader("./shaders/vs_color.vert", "./shaders/fs_color.frag");
	 Shader texture_shader("./shaders/vs_texture.vert", "./shaders/fs_texture.frag");

	 Material new_material;
	 new_material.add_shader("color", &color_shader);
	 new_material.add_shader("diffuse", &diffuse_shader);
	 new_material.add_shader("texture", &texture_shader);

	const auto tri_mesh = std::make_unique<RMeshTriangle>();
	const auto quad_mesh = std::make_unique<RMeshQuad>();
	const auto cube_mesh = std::make_unique<RMeshCube>();
	const auto line_mesh = std::make_unique<RMeshLine>();
	
	TextureManager tm;
	Texture box_tex(tm.load_texture("thing", "./img/thing.jpg"));
	Texture wall_tex(tm.load_texture("wall", "./img/wall.jpg"));

	Entity e1(cube_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e1.scale(glm::vec3(3,3,3));
	e1.translate(glm::vec3(0.0, 2.0, -6.0));
	
	Entity e2(tri_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e2.scale(glm::vec3(4,4,4));
	e2.translate(glm::vec3(6.0, 2.0, 4.0));

	Entity e3(quad_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e3.scale(glm::vec3(5,5,5));
	e3.translate(glm::vec3(4.0, 4.0, 3.0));
	
	Entity e4(tri_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	//e4.scale(glm::vec3(3.0, 3.0, 3.0));
	e4.rotate(glm::radians(-45.0f), glm::vec3(0.0, 1.0, 0.0));
	e4.translate(glm::vec3(4.0, 4.0, -2.0));

	Entity e5(quad_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e5.translate(glm::vec3(4.0, 4.0, -4.0));
	
	Entity e6(quad_mesh.get(), new_material, wall_tex, EntityType::TEXTURED_MODEL);
	e6.translate(glm::vec3(-6.0, 2.0, -2.0));
	
	Entity e7(quad_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	//e7.scale(glm::vec3(8,8,8));
	//e7.rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	e7.translate(glm::vec3(0.0, 2.0, 0.0));
	
	Entity e8(line_mesh.get(), new_material, 0, EntityType::LINE);
	e8.scale(glm::vec3(0.5f, 0.5f, 0.5f));
	e8.rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	Entity e9(cube_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	//e9.scale(glm::vec3(2.0, 2.0, 2.0));
	e9.translate(glm::vec3(0.0, 0.0, -20.0));

	Scene scene;
	scene.add_entity(&e1);
	scene.add_entity(&e2);
	scene.add_entity(&e3);
	scene.add_entity(&e4);
	scene.add_entity(&e5);
	scene.add_entity(&e6);
	scene.add_entity(&e7);
	scene.add_entity(&e8);
	scene.add_entity(&e9);
	
	
	constexpr int CUBE_MAX = 4096;
	constexpr float offset = 32.0f;
	constexpr float step = 1.0f;
	float x = -offset;
	float z = -offset;
	for (int i = 0; i < CUBE_MAX; ++i) {
		Entity* e = new Entity(cube_mesh.get(), new_material, wall_tex, EntityType::TEXTURED_MODEL);
		glm::vec3 bp(x, -2.0, z);
		e->translate(bp);
		e->set_base_position(bp);
		scene.add_entity(e);
		x += step;
		if (x >= offset) {
			x = -offset;
			z += step;
		}
	}

	// MeshData sphere_mesh_data;
	// if (!load_obj("./models/cube.obj", sphere_mesh_data)) {
	// 	std::cerr << "Model load failed.\n";
	// }
	// auto sphere_mesh = std::make_unique<RMeshModel>(sphere_mesh_data);
	// Entity ent_sphere(sphere_mesh.get(), diffuse_material, 0, EntityType::UNTEXTURED_MODEL);
	// //ent_teapot.rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// ent_sphere.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	// ent_sphere.translate(glm::vec3(-2.0f, 2.0f, -1.0f));
	// scene.add_entity(&ent_sphere);

	// MeshData suzanne_mesh_data;
	// if (!load_obj("./models/suzanne.obj", suzanne_mesh_data)) {
	// 	std::cerr << "Model load failed.\n";
	// }
	// auto suzanne_mesh = std::make_unique<RMeshModel>(suzanne_mesh_data);
	// Entity ent_suzanne(suzanne_mesh.get(), diffuse_material, 0, EntityType::UNTEXTURED_MODEL);
	// ent_suzanne.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	// ent_suzanne.translate(glm::vec3(5.0, 1.0, -3.0));
	// scene.add_entity(&ent_suzanne);

	// MeshData teapot_mesh_data;
	// if (!load_obj("./models/teapot.obj", teapot_mesh_data)) {
	// 	std::cerr << "Model load failed.\n";
	// }
	// auto teapot_mesh = std::make_unique<RMeshModel>(teapot_mesh_data);
	// Entity ent_teapot(teapot_mesh.get(), texture_material, 0, EntityType::UNTEXTURED_MODEL);
	// ent_teapot.scale(glm::vec3(2.0f, 2.0f, 2.0f));
	// ent_teapot.translate(glm::vec3(-20.0, 0.0, -15.0));
	// scene.add_entity(&ent_teapot);


	// auto light_mesh = std::make_unique<RMeshCube>();
	// Entity ent_light(light_mesh.get(), color_material, 0, EntityType::LIGHT);
	// ent_light.set_viewable_flag(false);
	// scene.add_entity(&ent_light);

	Light light(new_material, glm::vec3(0,0,0));
	light.set_color(glm::vec3(1.0, 0.0, 0.0));
	light.translate(glm::vec3(5.0f, 15.0f, 0.0f));
	scene.add_light(&light);

	////////////////

	auto camera = Camera(
		{0, 0, -5}, // pos
		{0, 0, 0}, // lookat
		{0, 1, 0}, // up
		config::SCREEN_W,
		config::SCREEN_H,
		0.1f,
		1000.0f
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
	double ang = 0.0;

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

		if (input->get_left_mouse_button_state()) {
			auto cursor = input->get_cursor_pos();
			//std::cout << cur.xpos << ", " << cur.ypos << "\n";)
			auto r = cast_ray(cursor, camera.get_projection(), camera.get_view());
			//std::cout << r.x << ", " << r.y << ", " << r.z << std::endl;

			int count = 0;
			for (auto e : scene.get_entities()) {
				bool b = ray_intersect_sphere(camera.get_camera_position(), r, e->get_base_position(), 1.0f);
				if (b) {
					//std::cout << "Cube " << count << " Intersection\n";
					e->translate(glm::vec3(0.0, 1.0, 0.0));
					break;
				}
				++count;
				// bool q = ray_intersect_sphere(camera.get_camera_position(), r, glm::vec3(0.0, 2.0, 0.0), 1.0f);
				// if (q) {
				// 	std::cout << "Quad Intersection\n";
				// }
			}
		}

		// for (auto e : scene.get_entities()) {
		// 	e->rotate(glm::radians(val), glm::vec3(0.0, 1.0, 0.0));
		// }

		scene.entities[8]->rotate(glm::radians(val), glm::vec3(1.0,1.0,1.0));
		scene.entities[scene.entities.size()-3]->rotate(glm::radians(glm::sin(val-1.5f)), glm::vec3(0.0,1.0,0.0));
		scene.entities[scene.entities.size()-2]->rotate(glm::radians(val), glm::vec3(0.0,1.0,0.0));

		// for (auto l : scene.lights) {
		// 	l->rotate(glm::radians(glm::sin(val)), glm::vec3(0.0,1.0,0.0));
		// }
		val = 1.0f;
		//ang += 0.1;
		camera.update(delta);

		video->begin_scene();

		video->renderer(camera, scene);

		video->end_scene();

		device->window_swap();
	}

	for (auto e : scene.entities) {
		e->get_mesh()->cleanup();
	}
}