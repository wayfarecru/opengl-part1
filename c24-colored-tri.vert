#version 330 core

in vec4 aPos; // vertex position: attribute
in vec4 aColor; // vertex color: attribute
out vec4 vColor; // varying color: varying

void main(void) {
	gl_Position = aPos;
	vColor = aColor;
}
