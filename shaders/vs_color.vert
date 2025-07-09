#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_col;

out vec3 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	
	gl_Position = projection * view * model * vec4(v_pos, 1);

    fragColor = v_col;
}