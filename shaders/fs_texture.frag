#version 400 core

in vec2 uv_coords;
out vec4 color;

uniform sampler2D tex_sampler0;
uniform sampler2D tex_sampler1;
//uniform sampler2D tex_sampler[5];


void main(){

	color = texture(tex_sampler0, uv_coords);
	color = texture(tex_sampler1, uv_coords);
}