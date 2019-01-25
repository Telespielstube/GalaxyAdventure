#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"
#include "Gate.h"
#include "ColBox.h"

float scaleFactor = 1.0f;

/** Constructor
*
*	@param	filename	path to the object file.
*	@param	renderer	holds the 3 matrices Model, View, Perspective information.
*
*/
Gate::Gate(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID) : RenderedObject(filename, renderer)
{
	texture = gateTexture;
	textureID = TextureID;

	// Erzeugt die KollisionsBox um das Gate
		// Erste KollisionsBox ist über das Ganze Gate	

	float x = 4.22;
	float y = 0.5;
	float z = 0.68;

	float xCol = 0.58;
	float yCol = 1;
	float zCol = 1.36;


	//  ******************** Erstellung Kollisionsbox ums gate   *********************************

		// Erste Kollisionsbox Main box dient zur erkennung das Schiff in der nähe ist zum Gate
	addColBox(new ColBox( - 5,  - 5,  - 3.2, 10, 10, 4));

	addColBox(new ColBox( - x,  - y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 4.2; y = 0.5; xCol = 0.6; yCol = 0.5;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 4.1; y = 1;	xCol = 0.6;	yCol = 0.25;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 4.0; y = 1.25;	xCol = 0.65;	yCol = 0.25;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.9; y = 1.5;	xCol = 0.65;	yCol = 0.25;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.8; y = 1.75;	xCol = 0.7;	yCol = 0.25;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.7; y = 2;	xCol = 0.7;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.65; y = 2.125; xCol = 0.75;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.55; y = 2.25; xCol = 0.75;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.5; y = 2.375; xCol = 0.75;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.4; y = 2.5; xCol = 0.8;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.3; y = 2.625; xCol = 0.8;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.2; y = 2.75; xCol = 0.8;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.1; y = 2.875; xCol = 0.85;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 3.0; y = 3.0; xCol = 0.9;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 2.8; y = 3.125; xCol = 1.0;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 2.65; y = 3.25; xCol = 1.1;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 2.5; y = 3.375; xCol = 1.1;	yCol = 0.125;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y,  - z, xCol, yCol, zCol));

	x = 0.5; y = 3.6; xCol = 1;	yCol = 0.58;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));

	x = 1; y = 3.5; xCol = 0.5;	yCol = 0.58;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y - yCol,  - z, xCol, yCol, zCol));

	x = 1.5; y = 3.4; xCol = 0.5;	yCol = 0.58;
	addColBox(new ColBox( - x,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( - x,  - y - yCol,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  + y,  - z, xCol, yCol, zCol));
	addColBox(new ColBox( + x - xCol,  - y - yCol,  - z, xCol, yCol, zCol));

	//////////////////////////////////////////////
	
}

/** Draws the object and aligns it.
*
*	@param	Model	Object to draw on screen.
*
*/
void Gate::draw(glm::mat4 &Model, GLuint programID)
{	
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
	glm::vec3 lightPositionGate = glm::vec3(.0, 13.0, .0);
	glUniform3f(glGetUniformLocation(programID, "LightPositionGate"), lightPositionGate.x, lightPositionGate.y, lightPositionGate.z);
	
	float angleY = 90.0f;
	glm::mat4 Save = Model;
	Model = glm::scale(Model, glm::vec3(1.0f * scaleFactor, 1.0f * scaleFactor, 1.0f * scaleFactor));
	Position p = getPosition();
	Model = glm::translate(Model, glm::vec3(p.getX(), p.getY(), p.getZ()));
	Model = glm::rotate(Model, xAngle, glm::vec3(1.0f, .0f, .0f));
	Model = glm::rotate(Model, yAngle, glm::vec3(.0f, 1.0f, .0f));
	m_renderer.sendMVP(Model);
	RenderedObject::drawVertices(Model);
	Model = Save;
}

std::vector <ColBox*> Gate::getColBox()
{
	return colBoxList;
}

void Gate::addColBox(ColBox *b)
{
	colBoxList.push_back(b);
}

float Gate::getScaleF()
{
	return scaleFactor;
}

/** Destructor of Gate object
*
*/
Gate::~Gate()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);

}