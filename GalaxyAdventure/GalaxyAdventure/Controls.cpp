#include <GLFW/glfw3.h>
#include "Controls.h"


Controls::Controls()
{
}

float Controls::moveSpaceship(GLFWwindow *window)
{
	float positionX = .0f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		positionX += .5f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		positionX -= .5f;
	}

	return positionX;
}

Controls::~Controls()
{
}
