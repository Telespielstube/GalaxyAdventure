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
		positionX += .1f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		positionX -= .1f;
	}

	return positionX;
}
float Controls::moveSpaceshipForward(GLFWwindow *window)
{
	float positionZ = .0f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		positionZ += .1f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		positionZ -= .1f;
	}
	return positionZ;
}
Controls::~Controls()
{
}
