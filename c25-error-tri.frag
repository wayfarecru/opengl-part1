#version 330 core

in vec3 vColor; // ERROR: varying color: varying
out vec4 FragColor; // fragment color: framebuffer

void main(void) {
	FragColor = vColor;
}
