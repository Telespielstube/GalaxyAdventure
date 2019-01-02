#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"
#include "ColBox.h"
#include "objects.hpp"
#include "Controls.h"

/** Constructor
*
*	@param	filename	path to the object file.
*	@param	renderer	holds the 3 matrices Model, View, Perspective information.
*
*/
Spaceship::Spaceship(const char *filename, Renderer &renderer, GLuint shipTexture, GLuint TextureID) : RenderedObject(filename, renderer), box1(-1,0,-2, 2, 2, 5)
{
	texture = shipTexture;
	textureID = TextureID;
}

/** Destructor
*/
Spaceship::~Spaceship() {}


void Spaceship::draw(glm::mat4 & Model, float programID)
{	
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
	glm::vec3 lightPositionSpaceship = glm::vec3(.0, 6.0, .0);
	glUniform3f(glGetUniformLocation(programID, "LightPositionSpaceship"), lightPositionSpaceship.x, lightPositionSpaceship.y, lightPositionSpaceship.z);

	glm::mat4 Save = Model;
	Model = glm::translate(Model, glm::vec3(xPosition, yPosition, zPosition));	
	m_renderer.sendMVP(Model);	
	RenderedObject::drawVertices(Model);
	Model = Save;
}


