#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#include <stdio.h>

const unsigned int WIN_W = 500; // window size in pixels, (Width, Height)
const unsigned int WIN_H = 500;

int main(void) {
	// start GLFW
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "Hello GLEW", NULL, NULL);
	glfwMakeContextCurrent(window);
	// start GLEW
	glewInit();
	// checking OpenGL version (optional)
	const char* strVersion = (const char*)(glGetString(GL_VERSION));
	printf("version = %s\n", strVersion);
	fflush(stdout);
	// main loop
	while (! glfwWindowShouldClose(window)) {
		// draw
		glClear(GL_COLOR_BUFFER_BIT);
		// GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// done
	glfwTerminate();
	return 0;
}
