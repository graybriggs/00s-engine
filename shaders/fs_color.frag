#version 330 core

in vec3 fragColor;

out vec4 color;

void main(){
	float ambient_strength = 1.0;
	vec3 result = ambient_strength * fragColor;
	color = vec4(result, 1.0);
}