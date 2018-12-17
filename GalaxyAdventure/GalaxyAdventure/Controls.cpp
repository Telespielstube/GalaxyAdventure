#include <GLFW/glfw3.h>
#include "Controls.h"


Controls::Controls()
{
}


float speed = 0.003f;
/** Moves the spaceship on the x axis.
*	
*/
float Controls::moveSpaceshipOnX(GLFWwindow *window)
{
	float positionX = .0f;

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		positionX += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		positionX -= speed;
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
		positionY += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		positionY -= speed;
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
		positionZ -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		positionZ += speed;
	}
	return positionZ;
}


Controls::~Controls()
{
}
