#pragma once
class Controls
{
public:
	Controls();

	float moveSpaceshipOnX(GLFWwindow *window);
	float moveSpaceshipOnY(GLFWwindow *window);
	float moveSpaceshipOnZ(GLFWwindow *window);
	~Controls();
};

