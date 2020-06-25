
#include <iostream>
#include <cmath>
#include <vector>

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "config.h"
#include "shader.h"
#include "timer.h"
#include "cube.h"
#include "triangle.h"

#include "device.h"
#include "video.h"

int main() {

	auto device = makeDevice(config::SCREEN_W, config::SCREEN_H);
	auto video = device->getVideoDriver();

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(device->window, GLFW_STICKY_KEYS, GL_TRUE);

	
	////////////////////////////
	////////////////////////////

	GLuint vertexArrayTriangle;
	glGenVertexArrays(1, &vertexArrayTriangle);
	glBindVertexArray(vertexArrayTriangle);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	constexpr float FOV = 45.0f; // ? 100.0f;

	/////////////////////////////

	Triangle tri;
	
	GLuint vertexbuffertri = tri.prepare_vertex_data();
	GLuint colorbuffertri = tri.prepare_color_data();

	Cube cube;
	GLuint vertexbuffer = cube.prepare_vertex_data();
	GLuint colorbuffer = cube.prepare_color_data();

	GLuint programID = load_shaders("vs.vert","fs.frag");

	glm::mat4 projection = glm::perspective(glm::radians(FOV), config::ASPECT_RATIO, 0.1f, 100.0f);

	Timer timer;
	timer.start_timer();
	   
	while (device->run()) {
		
		video->beginScene();


		glm::mat4 mvp;
		glm::mat4 cube_view;
		GLuint mvpID;

		for (int i = 0; i < 2; ++i) {

			double tf = timer.current_time() + i;

			glm::mat4 model_cube_r = glm::mat4(1.0f);
			model_cube_r *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)tf, glm::vec3(1.0f, 0.0f, 0.0f));
			model_cube_r *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)tf, glm::vec3(0.0f, 1.0f, 0.0f));
			model_cube_r *= glm::rotate(glm::mat4(1.0f), 1.75f*(float)tf, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 model_cube = glm::translate(model_cube_r, glm::vec3(std::sin(0.35f*timer.current_time())*2.0f,
				std::cos(0.52f*timer.current_time())*2.0f, std::sin(0.7f*timer.current_time())*2.0f));
			//glm::mat4 model_cube = model_cube_t * model_cube_r;

			cube_view = glm::lookAt(
				glm::vec3(0, 0, 10), // cam pos
				glm::vec3(0, 0, 0), // camera is looking at (origin)
				glm::vec3(0, 1, 0) // head up direction
			);



			mvp = projection * cube_view * model_cube;

			glUseProgram(programID);

			mvpID = glGetUniformLocation(programID, "mvp");
			glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glVertexAttribPointer(
				1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		}
		///
		glm::mat4 tri_view;

		tri_view = glm::lookAt(
			glm::vec3(0, 0, 10), // cam pos
			glm::vec3(0, 0, 0), // camera is looking at (origin)
			glm::vec3(0, 1, 0) // head up direction
		);
		
		glm::mat4 model_tri = glm::mat4(1.0f);
		
		model_tri = glm::translate(model_tri, glm::vec3(4.0, 6.0, -15.0));
		model_tri = glm::rotate(model_tri, -1.75f*(float)timer.current_time(), glm::vec3(0.0f, 0.0f, 1.0f));
		mvp = projection * tri_view * model_tri;

		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffertri);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffertri);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		video->endScene();


		//glfwSwapBuffers(device->window);
		//glfwPollEvents();

	}
	
	/*
	while (glfwGetKey(device->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(device->window) == 0);
	*/
}