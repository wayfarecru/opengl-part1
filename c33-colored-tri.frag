#version 330 core

in vec4 vColor; // varying color: varing
out vec4 FragColor; // fragment color: framebuffer

void main(void) {
	FragColor = vColor;
}
