#pragma once
class WindowInit
{

/*	Initalisieren des Fensters

	@autor	
*/
public:
	WindowInit();
	bool initializeGLFW();
	GLFWwindow* createMainWindow(int width, int height, const char *title, int xPosition, int yPosition);
	~WindowInit();
};

