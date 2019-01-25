#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include "Renderer.h"
#include "Position.h"
#include "ColBox.h"

class RenderedObject
{
public:
	RenderedObject(const char *filename, Renderer &renderer);
	virtual ~RenderedObject();
	virtual void drawVertices(glm::mat4 &Model);
	virtual void setPosition(Position p);
	void addColBox(ColBox *b);  // Zum hinzufügen von Kollisionsboxen.
	std::vector <ColBox*> getColBox();	// Speichert die Kolisionsboxen in einem Array, Index 0 = Main Kollisonsbox um das Gate
	Position getPosition();		
	
	

protected:	
	Renderer &m_renderer;

	GLuint VertexArrayID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;

	GLuint texture;
	GLuint textureID;	
	std::vector<ColBox*> colBoxList;

private:
	Position position;	
	
	
};
