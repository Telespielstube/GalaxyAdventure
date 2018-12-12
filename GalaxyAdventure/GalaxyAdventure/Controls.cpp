#include <GLFW/glfw3.h>
#include "Controls.h"


Controls::Controls()
{
}

/** Moves the spaceship on the x axis.
*	
*/
float Controls::moveSpaceshipOnX(GLFWwindow *window)
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

/** Moves the spaceship on the y axis.
*
*/
float Controls::moveSpaceshipOnY(GLFWwindow *window)
{
	float positionY = .0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		positionY += .1f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		positionY -= .1f;
	}
	return positionY;
}

/** Moves the spaceship on the z axis.
*
*/
float Controls::moveSpaceshipOnZ(GLFWwindow *window)
{
	float positionZ = .0f;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		positionZ -= .1f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		positionZ += .1f;
	}
	return positionZ;
}


Controls::~Controls()
{
}
