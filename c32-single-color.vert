#version 330 core

in vec4 aPos; // vertex position: attribute

void main(void) {
	gl_Position = aPos;
}
