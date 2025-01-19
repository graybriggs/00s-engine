#include <cstdio>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "material.h"

//Material::Material(GLuint vertex_shader_id, GLuint fragment_shader_id) {
Material::Material(GLuint vertex_shader_id, GLuint fragment_shader_id) {

	printf("Linking material program\n");
	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    
	GLint result = GL_FALSE;
	int info_log_length;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> err_msg(info_log_length + 1);
		glGetProgramInfoLog(program_id, info_log_length, NULL, &err_msg[0]);
		printf("%s\n", &err_msg[0]);
	}

    glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}

GLuint Material::handle() {
    return program_id;
}