#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include "RenderedObject.h"

/*	Enth�lt das Objekt eine Sternes

	@autor	Martina Br�ning
*/

class Star : public RenderedObject
{
public:
	Star(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID);	
	virtual ~Star();
	virtual void draw(glm::mat4 &Model, GLuint programID);	
};

