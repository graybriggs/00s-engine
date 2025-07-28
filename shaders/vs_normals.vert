#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec2 v_tex_uv;
layout (location = 2) in vec3 v_normal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = view * model * vec4(v_pos, 1.0);
    mat3 normal_matrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = normalize(normal_matrix * v_normal);
}

