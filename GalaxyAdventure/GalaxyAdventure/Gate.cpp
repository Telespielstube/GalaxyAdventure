#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"
#include "Gate.h"

/** Funtion to read the data from the file and passing the data to the vertexshader and fragmentshader.
*
*	@param	filename	path of the obj. file.
*
*/
Gate::Gate(const char *filename, Renderer &renderer) : RenderedObject(filename, renderer)
{
}

/** Aligns the ship to the right position on screen.
*
*/
void Gate::alignGateOnScreen(glm::mat4 Model)
{
	Model = glm::translate(Model, glm::vec3(.0f, .0f, .0f));
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

void Gate::draw(glm::mat4 &Model)
{
	float scaleFactor = 3.0f;
	float angleX = -45.0f;
	float angleY = 90.0f;
	glm::mat4 Save = Model;
	Model = glm::scale(Model, glm::vec3(1.0f * scaleFactor, 1.0f * scaleFactor, 1.0f * scaleFactor));
	Model = glm::translate(Model, glm::vec3(xPosition, yPosition, zPosition));
	Model = glm::rotate(Model, angleX, glm::vec3(1.0f, .0f, .0f));
	Model = glm::rotate(Model, angleY, glm::vec3(.0f, 1.0f, .0f));
	m_renderer.sendMVP(Model);	
	RenderedObject::draw(Model);
	Model = Save;
}
