#version 330 core

in vec3 frag_pos;
in vec3 frag_color;
in vec3 frag_normal;

out vec4 color;

uniform vec3 light_pos;

void main(){

    vec3 ambient_color = vec3(0.1);
    vec3 light_color = vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 res = (ambient_color + diffuse) * frag_color;

	color = vec4(res, 1.0);
}