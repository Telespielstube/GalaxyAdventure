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
*	@param	filename		path to the object file.
*	@param	renderer		holds the 3 matrices Model, View, Perspective information.
*	@param	gateTexture		rgb data from the image.
*	@param	TextureID		ID for the texture of the object.
*
*/
Gate::Gate(const char *filename, Renderer &renderer, GLuint gateTexture, GLuint TextureID) : RenderedObject(filename, renderer)
{
	texture = gateTexture;
	textureID = TextureID;

	
	addColCicle(new ColCicle(Position(0.0f, 0.0f, -0.2f), 4.25f, 0.8f));	
	// Kollisionsbox die von der Oberen abgezogen wird
	addColCicle(new ColCicle(Position(0.0f, 0.0f, -0.2f), 3.7f, 0.8f));

	
	
}

/** Draws the object and aligns it.
*
*	@param	Model	The object to draw on screen.
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
	Position p = getPosition();
	Model = glm::translate(Model, glm::vec3(p.getX(), p.getY(), p.getZ()));
	Model = glm::rotate(Model, p.getAngleX(), glm::vec3(1.0f, .0f, .0f));
	Model = glm::rotate(Model, p.getAngleY(), glm::vec3(.0f, 1.0f, .0f));
	//std::cout << p.getAngleX() << " " << p.getAngleY() << " " <<  std::endl;
	m_renderer.sendMVP(Model);
	RenderedObject::drawVertices(Model);
	Model = Save;
}

/** Gets the scale factor
*
*	@return scale factor.
*/
float Gate::getScaleF()
{
	return scaleFactor;
}

// Destructor of Gate object
Gate::~Gate()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}