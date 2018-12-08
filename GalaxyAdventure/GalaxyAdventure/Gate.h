#pragma once

class Gate
{
public:
	// Constructor
	Gate(const char *filename);

	void drawGate();
	void alignGateOnScreen(glm::mat4 Model);
	~Gate();
};

