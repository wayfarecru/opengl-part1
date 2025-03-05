#version 330 core

layout (location = 5) in vec4 vertexPos; // attribute

void main(void) {
	gl_Position = vertexPos;
}
