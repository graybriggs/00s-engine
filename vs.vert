#version 430 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_col;

//out vec4 fragColor;
out vec4 varyingColor;

uniform mat4 mvp;

void main() {
	
	gl_Position = mvp * vec4(v_pos,1);

	varyingColor = vec4(v_pos,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
	//fragColor = v_col;

}