#pragma once
#include "RenderedObject.h"

class Gate : public RenderedObject
{
public:
	// Constructor
	Gate(const char *filename, Renderer &renderer);

	void alignGateOnScreen(glm::mat4 Model);
	virtual ~Gate();
	virtual void draw(glm::mat4 & Model);
};

