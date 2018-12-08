#include <GLFW/glfw3.h>
#include "Controls.h"



Controls::Controls()
{
}

float Controls::moveSpaceship(GLFWwindow *window)
{
	float angleX = .0f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		angleX += .1f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		angleX -= .1f;
	}

	return angleX;
}

Controls::~Controls()
{
}
