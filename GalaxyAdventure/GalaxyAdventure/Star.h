#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include "RenderedObject.h"

class Star : public RenderedObject
{
public:
	Star(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID);
	
	virtual ~Star();
	virtual void draw(glm::mat4 &Model, GLuint programID);
	void starField(Star star);
};

