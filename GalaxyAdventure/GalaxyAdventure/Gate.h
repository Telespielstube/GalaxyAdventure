#pragma once
#include "RenderedObject.h"

class Gate : public RenderedObject
{
public:
	// Constructor
	Gate(const char *filename, Renderer &renderer);

	virtual ~Gate();
	virtual void draw(glm::mat4 & Model);
	ColBox box1;
};

