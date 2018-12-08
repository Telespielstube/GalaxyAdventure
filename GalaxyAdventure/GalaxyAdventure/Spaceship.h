#pragma once
#include "RenderedObject.h"

#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 

class Spaceship : public RenderedObject
{
public:
	// Constructor
	Spaceship(const char *filename);
	// Destructor
	virtual ~Spaceship();
};

