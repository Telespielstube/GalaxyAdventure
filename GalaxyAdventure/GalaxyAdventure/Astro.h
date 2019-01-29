#pragma once
#include "RenderedObject.h"

/*	Objekt eines Asteroiden

	@autor	Vassilios Tsankis s0558527
*/
class Astro: public RenderedObject
{
public:	
	Astro(const char *filename, Renderer &renderer, GLuint Texture, GLuint TextureID, float scaleF);
	virtual ~Astro();
	virtual void draw(glm::mat4 & Model, GLuint programID);	
	float getScaleF(); 
	void setDirection(float x, float y, float z);
	void setScaleF(float s);

private:
	float scaleFactor;
	float speed;
	float dX, dY, dZ;	
};

