#version 330 core

in vec4 aPos; // vertex position: attribute
in vec4 aColor; // vertex color: attribute
out vec4 vColor; // varying color: varying
uniform float uTheta; // rotation angle: uniform

void main(void) {
	gl_Position.x = aPos.x * cos(uTheta) - aPos.y * sin(uTheta);
	gl_Position.y = aPos.x * sin(uTheta) + aPos.y * cos(uTheta);
	gl_Position.zw = aPos.zw;
	vColor = aColor;
}
