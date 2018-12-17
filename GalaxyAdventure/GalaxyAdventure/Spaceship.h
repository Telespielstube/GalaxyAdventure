#pragma once
#include "RenderedObject.h"

#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include "ColBox.h"

class Spaceship : public RenderedObject
{
public:
	// Constructor
	Spaceship(const char *filename, Renderer &renderer);

	// Destructor
	virtual ~Spaceship();

	virtual void draw(glm::mat4 &Model);

	ColBox box1;
};

