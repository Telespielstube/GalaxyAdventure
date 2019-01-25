#pragma once
#include "RenderedObject.h"

class Gate : public RenderedObject
{
public:
	// Constructor
	Gate(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID);
	virtual ~Gate();
	virtual void draw(glm::mat4 & Model, GLuint programID);	// Zeichnet das Tor.
	
	
	float getScaleF(); // Gibt den Scalefactor zurück

};

