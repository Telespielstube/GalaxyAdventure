#pragma once
#include "RenderedObject.h"

class Gate : public RenderedObject
{
public:
	// Constructor
	Gate(const char *filename);

	void alignGateOnScreen(glm::mat4 Model);
	virtual ~Gate();
};

