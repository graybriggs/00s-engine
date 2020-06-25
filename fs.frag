#version 430 core

//in vec3 fragColor;
in vec4 varyingColor;

out vec4 color;

void main(){

	color = varyingColor;
 
}