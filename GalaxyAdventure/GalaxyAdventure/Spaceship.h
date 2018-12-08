#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

class Spaceship
{
public:
	// Constructor
	Spaceship(const char *filename);
	
	void drawSpaceShip();

	// Destructor
	~Spaceship();
};

