#version 330 core

out vec4 color;

void main() {
    vec3 white = vec3(1.0, 1.0, 1.0);
    vec3 gray = vec3(0.3, 0.3, 0.3);
    color = vec4(gray, 1.0);
}
