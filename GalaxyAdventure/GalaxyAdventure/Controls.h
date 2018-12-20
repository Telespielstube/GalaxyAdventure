#pragma once
class Controls
{
public:
	Controls();

	float moveSpaceshipOnX(GLFWwindow *window);
	float moveSpaceshipOnY(GLFWwindow *window);
	float moveSpaceshipOnZ(GLFWwindow *window);

	float CamOnX(GLFWwindow *window);
	float CamOnY(GLFWwindow *window);
	float CamOnZ(GLFWwindow *window);
	~Controls();
};

