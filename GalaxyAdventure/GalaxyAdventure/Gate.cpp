#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"
#include "Gate.h"

/** Constructor
*
*	@param	filename	path to the object file.
*	@param	renderer	holds the 3 matrices Model, View, Perspective information.
*
*/
Gate::Gate(const char *filename, Renderer &renderer) : RenderedObject(filename, renderer)
{
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

/** Draws the object and aligns it.
*
*	@param	Model	Object to draw on screen.
*
*/
void Gate::draw(glm::mat4 &Model)
{
	float scaleFactor = 3.0f;
	float angleY = 90.0f;
	glm::mat4 Save = Model;
	Model = glm::scale(Model, glm::vec3(1.0f * scaleFactor, 1.0f * scaleFactor, 1.0f * scaleFactor));
	Model = glm::translate(Model, glm::vec3(xPosition, yPosition, zPosition));
	Model = glm::rotate(Model, xAngle, glm::vec3(1.0f, .0f, .0f));
	Model = glm::rotate(Model, yAngle, glm::vec3(.0f, 1.0f, .0f));
	m_renderer.sendMVP(Model);	
	RenderedObject::drawVertices(Model);
	Model = Save;
}