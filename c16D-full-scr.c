#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma warning(disable: 4711 4710 4100)
#include <stdio.h>
#include <string.h> // for strrchr()

const unsigned int WIN_W = 1024; // window size in pixels, (Width, Height)
const unsigned int WIN_H = 768;
#if 0 // full screen setting !
const unsigned int WIN_X = 100; // window position in pixels, (X, Y)
const unsigned int WIN_Y = 100;
#endif

void refreshFunc(GLFWwindow* window) {
	// refresh
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();
	// GLFW action
	glfwSwapBuffers(window);
}

GLfloat clr[4] = { 0.933F, 0.769F, 0.898F, 1.0F };

void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case 'Q': clr[0] += 0.01F; if (clr[0] > 1.0F) clr[0] = 1.0F; break;
	case 'W': clr[1] += 0.01F; if (clr[1] > 1.0F) clr[1] = 1.0F; break;
	case 'E': clr[2] += 0.01F; if (clr[2] > 1.0F) clr[2] = 1.0F; break;
	case 'A': clr[0] -= 0.01F; if (clr[0] < 0.0F) clr[0] = 0.0F; break;
	case 'S': clr[1] -= 0.01F; if (clr[1] < 0.0F) clr[1] = 0.0F; break;
	case 'D': clr[2] -= 0.01F; if (clr[2] < 0.0F) clr[2] = 0.0F; break;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
	glClearColor(clr[0], clr[1], clr[2], clr[3]);
}

int main(int argc, char* argv[]) {
	// get your program name
#if defined(_WIN32) || defined(_WIN64)
	char* win_name = (strrchr(argv[0], '\\') == NULL) ? argv[0] : (strrchr(argv[0], '\\') + 1);
#else // Unix, Linux, MacOS
	char* win_name = (strrchr(argv[0], '/') == NULL) ? argv[0] : (strrchr(argv[0], '/') + 1);
#endif
	// start GLFW & GLEW
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, win_name, glfwGetPrimaryMonitor(), NULL);
#if 0
	glfwSetWindowPos(window, WIN_X, WIN_Y);
#endif
	glfwMakeContextCurrent(window);
	glewInit();
	// prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(clr[0], clr[1], clr[2], clr[3]);
	// main loop
	while (! glfwWindowShouldClose(window)) {
		// draw
		glClear(GL_COLOR_BUFFER_BIT);
		glFinish();
		// GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// done
	glfwTerminate();
	return 0;
}
