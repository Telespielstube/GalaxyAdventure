#pragma once

/*	Zur steuerung des Schiffes

	@autor	Martina Br�ning
*/
class Controls
{
public:
	Controls();

	float moveSpaceshipOnX(GLFWwindow *window, float speed);
	float moveSpaceshipOnY(GLFWwindow *window, float speed);
	float moveSpaceshipOnZ(GLFWwindow *window, float speed);
	
	~Controls();
};

