#pragma once
class Controls
{
public:
	Controls();

	float moveSpaceshipOnX(GLFWwindow *window, float speed);
	float moveSpaceshipOnY(GLFWwindow *window, float speed);
	float moveSpaceshipOnZ(GLFWwindow *window, float speed);

	float CamOnX(GLFWwindow *window, float speed);
	float CamOnY(GLFWwindow *window, float speed);
	float CamOnZ(GLFWwindow *window, float speed);
	~Controls();
};

