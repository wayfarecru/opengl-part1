#version 330 core

in vec4 aPos; // vertex position: attribute
in vec4 aColor; // vertex color: attribute
out vec4 vColor; // varying color: varying
uniform float uTheta; // rotation angle: uniform

void main(void) {
	gl_Position.z = aPos.z * cos(uTheta) - aPos.x * sin(uTheta);
	gl_Position.x = aPos.z * sin(uTheta) + aPos.x * cos(uTheta);
	gl_Position.yw = aPos.yw;
	gl_Position.z *= -1.0F; // negation
	vColor = aColor;
}
