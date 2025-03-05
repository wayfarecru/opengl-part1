#version 330 core

in vec4 vColor; // varying color: varying
out vec4 FragColor; // fragment color: framebuffer
uniform float uTheta; // roration angle: uniform

void main(void) {
	float w = 0.25F * cos(3.0F * uTheta) + 0.75F;
	FragColor = vColor * vec4(w, w, w, 1.0F);
}
