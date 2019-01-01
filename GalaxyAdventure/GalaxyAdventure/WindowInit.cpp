#include <stdlib.h>
#include <stdio.h>
#include <GLFW\glfw3.h>
#include "WindowInit.h"

WindowInit::WindowInit()
{
}


//Initializes the OpenGL library GLFW.
bool WindowInit::initializeGLFW()
{
	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return true;
}

/** Creates the main windows where the game happens.
*
*	@param	width		width of the window.
*	@param	height		height of the window.
*	@param	title		title of the window.
*	@param	xPosition	xPosition on screen.
*	@param	yPosition	yPosition on screen.
*
*/
GLFWwindow* WindowInit::createMainWindow(int width, int height, const char *title, int xPosition, int yPosition)
{
	GLFWwindow *window;
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return NULL;
	}

	//Sets the postion for the window
	glfwSetWindowPos(window, xPosition, yPosition);
	glfwMakeContextCurrent(window); //

	return window;
}

WindowInit::~WindowInit()
{
}
