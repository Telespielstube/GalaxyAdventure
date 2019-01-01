#pragma once
class WindowInit
{

public:
	WindowInit();
	bool initializeGLFW();
	GLFWwindow* createMainWindow(int width, int height, const char *title, int xPosition, int yPosition);
	~WindowInit();
};

