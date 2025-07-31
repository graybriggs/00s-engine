#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_col;

out VS_OUT {
    vec3 fragColor;
} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	
    //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
	gl_Position = projection * view * model * vec4(v_pos, 1.0);
    //gl_Position = vec4(v_pos, 1.0);
    vs_out.fragColor = vec3(0.5, (v_pos.y + 16.0) / 64.0 - 0.2, 0.6);
}