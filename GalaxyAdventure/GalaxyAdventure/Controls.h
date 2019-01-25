#pragma once
class Controls
{
public:
	Controls();

	float moveSpaceshipOnX(GLFWwindow *window, float speed);
	float moveSpaceshipOnY(GLFWwindow *window, float speed);
	float moveSpaceshipOnZ(GLFWwindow *window, float speed);
	
	~Controls();
};

