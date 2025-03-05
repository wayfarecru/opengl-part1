#ifndef __cplusplus
#error This file works only with C++
#endif

#include <iostream>
using namespace std;

#pragma warning(disable: 4711 4710 4100 4514 4626 4774 4365 4625 4464 4571 4201 5026 5027 5039 4819)

#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
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

const char* vertFileName = "c33-colored-tri.vert";
const char* fragFileName = "c33-colored-tri.frag";

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

glm::vec4 vertPos[] = { // 9 points
	{ -0.4F, -0.8F, 0.0F, 1.0F, },
	{ +0.4F, -0.8F, 0.0F, 1.0F, },
	{ -0.4F, -0.4F, 0.0F, 1.0F, },
	{ +0.5F, -0.4F, 0.0F, 1.0F, },
	{ -0.5F, +0.0F, 0.0F, 1.0F, },
	{ +0.5F, +0.0F, 0.0F, 1.0F, },
	{ -0.6F, +0.4F, 0.0F, 1.0F, },
	{ +0.6F, +0.4F, 0.0F, 1.0F, },
	{ -0.8F, +0.8F, 0.0F, 1.0F, },
};

glm::vec4 vertFan[] = { // 6 points
	{ -0.4F, -0.8F, 0.0F, 1.0F, }, // 0
	{ +0.4F, -0.8F, 0.0F, 1.0F, }, // 1
	{ +0.5F, -0.4F, 0.0F, 1.0F, }, // 3
	{ +0.5F, +0.0F, 0.0F, 1.0F, }, // 5
	{ +0.6F, +0.4F, 0.0F, 1.0F, }, // 7
	{ -0.8F, +0.8F, 0.0F, 1.0F, }, // 8
};

glm::vec4 vertQuad[] = { // 9 points
	{ -0.4F, -0.8F, 0.0F, 1.0F, },
	{ +0.4F, -0.8F, 0.0F, 1.0F, },
	{ +0.5F, -0.4F, 0.0F, 1.0F, },
	{ -0.4F, -0.4F, 0.0F, 1.0F, },
	{ -0.5F, +0.0F, 0.0F, 1.0F, },
	{ +0.5F, +0.0F, 0.0F, 1.0F, },
	{ +0.6F, +0.4F, 0.0F, 1.0F, },
	{ -0.6F, +0.4F, 0.0F, 1.0F, },
	{ -0.8F, +0.8F, 0.0F, 1.0F, },
};

glm::vec4 vertColor[] = {
	{ 1.0F, 0.4F, 0.4F, 1.0F, }, // red
	{ 0.4F, 1.0F, 0.4F, 1.0F, }, // green
	{ 0.4F, 0.4F, 1.0F, 1.0F, }, // blue
	{ 1.0F, 0.4F, 0.4F, 1.0F, }, // red
	{ 0.4F, 1.0F, 0.4F, 1.0F, }, // green
	{ 0.4F, 0.4F, 1.0F, 1.0F, }, // blue
	{ 1.0F, 0.4F, 0.4F, 1.0F, }, // red
	{ 0.4F, 1.0F, 0.4F, 1.0F, }, // green
	{ 0.4F, 0.4F, 1.0F, 1.0F, }, // blue
};

void updateFunc(void) {
	// do nothing
}

int primKind = 4; // triangles

void drawFunc(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0F, 1.0F);
	glClearDepthf(1.0F);
	// clear in gray color
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// provide the vertex attributes
	GLuint locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertPos[0]));
	// provide the color attributes
	GLuint locColor = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(locColor);
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertColor[0]));
	// draw a primitive
	switch (primKind) {
	case 0: // point
		glPointSize(9.0F); // big point !
		glDrawArrays(GL_POINTS, 0, 9);
		break;
	case 1: // lines
		glLineWidth(5.0F); // wide line
		glDrawArrays(GL_LINES, 0, 9);
		break;
	case 2: // line strip
		glLineWidth(5.0F); // wide line
		glDrawArrays(GL_LINE_STRIP, 0, 9);
		break;
	case 3: // line loop
		glLineWidth(5.0F); // wide line
		glDrawArrays(GL_LINE_LOOP, 0, 9);
		break;
	default:
	case 4: // triangles
		glDrawArrays(GL_TRIANGLES, 0, 9);
		break;
	case 5: // triangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);
		break;
	case 15: // triangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);
		glDisableVertexAttribArray(locColor);
		glVertexAttrib4f(locColor, 1.0F, 0.0F, 0.0F, 1.0F);
		glPointSize(9.0F); // big point !
		glDrawArrays(GL_POINTS, 0, 9);
		break;
	case 6: // triangle fan
		glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertFan[0]));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		break;
	case 16: // triangle fan
		glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertFan[0]));
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		glDisableVertexAttribArray(locColor);
		glVertexAttrib4f(locColor, 1.0F, 0.0F, 0.0F, 1.0F);
		glPointSize(9.0F); // big point !
		glDrawArrays(GL_POINTS, 0, 6);
		break;
	case 7: // quad
		glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertQuad[0]));
		glDrawArrays(GL_QUADS, 0, 9);
		break;
	case 8: // quad strip
		glDrawArrays(GL_QUAD_STRIP, 0, 9);
		break;
	}
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
	// argument processing
	if (argc > 1) {
		primKind = strtol( argv[1], nullptr, 10 );
	}
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
	glClearColor(0.2F, 0.2F, 0.2F, 1.0F);
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
