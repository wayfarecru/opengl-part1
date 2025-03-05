#ifndef __cplusplus
#error This file works only with C++
#endif

#include <iostream>
using namespace std;

#pragma warning(disable: 4711 4710 4100 4514 4626 4774 4365 4625 4464 4571 4201 5026 5027 5039)

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp> // for glm::to_string()
#include <glm/gtc/type_ptr.hpp> // for glm::value_ptr( )

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma warning(disable: 4711 4710 4100)

#include "./common.c"

const unsigned int WIN_W = 500; // window size in pixels, (Width, Height)
const unsigned int WIN_H = 500;
const unsigned int WIN_X = 100; // window position in pixels, (X, Y)
const unsigned int WIN_Y = 100;

const char* vertFileName = "c32-single-color.vert";
const char* fragFileName = "c32-single-color.frag";

GLuint vert = 0; // vertex shader ID number
GLuint frag = 0; // fragment shader ID number
GLuint prog = 0; // shader program ID number

void initFunc(void) {
	const char* vertSource = loadFile( vertFileName );
	const char* fragSource = loadFile( fragFileName );
	char buf[1024]; // mesg buffer
	GLint status; // for glGetShaderiv()
	// vert: vertex shader
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertSource, nullptr);
	glCompileShader(vert); // compile to get .OBJ
	glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
	printf("vert compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(vert, sizeof(buf), nullptr, buf);
	printf("vert log = [%s]\n", buf);
	// frag: fragment shader
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragSource, nullptr);
	glCompileShader(frag); // compile to get .OBJ
	glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
	printf("frag compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(frag, sizeof(buf), nullptr, buf);
	printf("frag log = [%s]\n", buf);
	// prog: program
	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glLinkProgram(prog); // link to get .EXE
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("prog link status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), nullptr, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("prog validate status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), nullptr, buf);
	printf("validate log = [%s]\n", buf);
	fflush(stdout);
	// execute it!
	glUseProgram(prog);
	// done
	free( (void*)vertSource );
	free( (void*)fragSource );
}

glm::vec4 vertRed[] = {
	{ +0.4F, -0.8F, -0.5F, 1.0F, },
	{ +0.6F, -0.8F, -0.5F, 1.0F, },
	{ +0.6F, +0.8F, +0.5F, 1.0F, },
	{ +0.6F, +0.8F, +0.5F, 1.0F, },
	{ +0.4F, +0.8F, +0.5F, 1.0F, },
	{ +0.4F, -0.8F, -0.5F, 1.0F, },
};

glm::vec4 vertGreen[] = {
	{ +0.8F, +0.4F, -0.5F, 1.0f, },
	{ +0.8F, +0.6F, -0.5F, 1.0f, },
	{ -0.8F, +0.6F, +0.5F, 1.0f, },
	{ -0.8F, +0.6F, +0.5F, 1.0f, },
	{ -0.8F, +0.4F, +0.5F, 1.0f, },
	{ +0.8F, +0.4F, -0.5F, 1.0f, },
};

glm::vec4 vertBlue[] = {
	{ -0.4F, +0.8F, -0.5F, 1.0F, },
	{ -0.6F, +0.8F, -0.5F, 1.0F, },
	{ -0.6F, -0.8F, +0.5F, 1.0F, },
	{ -0.6F, -0.8F, +0.5F, 1.0F, },
	{ -0.4F, -0.8F, +0.5F, 1.0F, },
	{ -0.4F, +0.8F, -0.5F, 1.0F, },
};

glm::vec4 vertYellow[] = {
	{ -0.8F, -0.4F, -0.5F, 1.0f, },
	{ -0.8F, -0.6F, -0.5F, 1.0f, },
	{ +0.8F, -0.6F, +0.5F, 1.0f, },
	{ +0.8F, -0.6F, +0.5F, 1.0f, },
	{ +0.8F, -0.4F, +0.5F, 1.0f, },
	{ -0.8F, -0.4F, -0.5F, 1.0f, },
};

void updateFunc(void) {
	// do nothing
}

void drawFunc(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0F, 1.0F);
	glClearDepthf(1.0F);
	// clear in gray color
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// provide the vertex attributes
	GLuint locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	GLuint locColor = glGetUniformLocation(prog, "uColor");
	// red 
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertRed[0]));
	glUniform4f(locColor, 1.0F, 0.3F, 0.3F, 1.0F); // (light) red
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// green 
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertGreen[0]));
	glUniform4f(locColor, 0.3F, 1.0F, 0.3F, 1.0F); // (light) green
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// blue
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertBlue[0]));
	glUniform4f(locColor, 0.3F, 0.3F, 1.0F, 1.0F); // (light) blue
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// yellow
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertYellow[0]));
	glUniform4f(locColor, 1.0F, 1.0F, 0.3F, 1.0F); // (light) yellow
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// done
	glFinish();
}

void refreshFunc(GLFWwindow* window) {
	// refresh
	drawFunc();
	// GLFW action
	glfwSwapBuffers(window);
}

void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
}

int main(int argc, char* argv[]) {
	const char* basename = getBaseName( argv[0] );
	// start GLFW & GLEW
	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, basename, nullptr, nullptr);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);
	glewInit();
	// prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.5F, 0.5F, 0.5F, 1.0F);
	// main loop
	initFunc();
	while (! glfwWindowShouldClose(window)) {
		// animation loop
		updateFunc();
		drawFunc();
		// GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// done
	glfwTerminate();
	return 0;
}
