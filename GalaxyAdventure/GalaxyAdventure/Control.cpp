#include <GLFW/glfw3.h>
#include "Control.h"
extern GLFWwindow *window;


Control::Control()
{
}

float Control::moveSpaceship()
{
	float angleX = .0f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		angleX += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		angleX -= 0.1f;
	}

	return angleX;
}

Control::~Control()
{
}
