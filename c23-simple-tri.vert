#version 330 core

in vec4 vertexPos; // attribute

void main(void) {
	gl_Position = vertexPos;
}
