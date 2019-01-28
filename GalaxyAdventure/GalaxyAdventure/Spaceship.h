#pragma once
#include "RenderedObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include "ColBox.h"

/*	Enthält das Objekt des Schiffes

	@autor	Martina Brüning
*/

class Spaceship : public RenderedObject
{
public:
	Spaceship(const char *filename, Renderer &renderer, GLuint shipTexture, GLuint TextureID);
	virtual ~Spaceship();
	virtual void draw(glm::mat4 &Model, GLuint programID);
	
};

