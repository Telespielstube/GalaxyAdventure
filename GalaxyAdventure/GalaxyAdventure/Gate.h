#pragma once
#include "RenderedObject.h"

class Gate : public RenderedObject
{
public:
	// Constructor
	Gate(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID);
	virtual ~Gate();
	virtual void draw(glm::mat4 & Model);	// Zeichnet das Tor.
	std::vector <ColBox*> getColBox();	// Speichert die Kolisionsboxen in einem Array, Index 0 = Main Kollisonsbox um das Gate
	void addColBox(ColBox *b);  // Zum hinzufügen von Kollisionsboxen.
	float getScaleF(); // Gibt den Scalefactor zurück

private:
	std::vector<ColBox*> colBoxList;
};

