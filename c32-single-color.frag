#version 330 core

uniform vec4 uColor; // uniform color: uniform
out vec4 FragColor; // fragment color: framebuffer

void main(void) {
	FragColor = uColor;
}
