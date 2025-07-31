#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_col;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 frag_color;

void main() {
	
	gl_Position = projection * view * model * vec4(v_pos, 1.0);
    frag_color = v_col;
}