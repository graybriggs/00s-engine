#version 330 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_col;
layout(location = 2) in vec3 v_normal;

out vec3 frag_pos;
out vec3 frag_color;
out vec3 frag_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	
	gl_Position = projection * view * model * vec4(v_pos, 1);
    frag_pos = vec3(model * vec4(v_pos, 1.0));
    frag_color = v_col;
    //normal = v_normal;
    frag_normal = mat3(transpose(inverse(model))) * v_normal; 
}