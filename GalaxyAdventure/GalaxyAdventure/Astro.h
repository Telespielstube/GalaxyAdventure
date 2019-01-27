#pragma once
#include "RenderedObject.h"

class Astro: public RenderedObject
{
public:
	// Constructor
	Astro(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID, float scaleF);
	virtual ~Astro();
	virtual void draw(glm::mat4 & Model, GLuint programID);	
	float getScaleF(); // Gibt den Scalefactor zurück
	void setDirection(float x, float y, float z);
	void setScaleF(float s);

private:
	float scaleFactor;
	float speed;
	float dX, dY, dZ;	
};

