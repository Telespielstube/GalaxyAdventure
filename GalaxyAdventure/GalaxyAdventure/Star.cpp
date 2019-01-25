#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "objloader.h"
#include "objects.hpp"
#include "Star.h"

/** Constructor
*
*	@param	filename		path to the object file.
*	@param	renderer		holds the 3 matrices Model, View, Perspective information.
*	@param  ShipTexture		Texture of the star.
*	@param	TextureID		id for the texture of the star.
*
*/
Star::Star(const char *filename, Renderer &renderer, GLuint starTexture, GLuint TextureID) : RenderedObject(filename, renderer)
{
	texture = starTexture;
	textureID = TextureID;
}

/** Draws the star on screen.
*
*	@param	Model			the scene in which the game takes place
*	@param programID		an id for the current application
*
*/
void Star::draw(glm::mat4 &Model, GLuint programID) 
{	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureID, 0);
	glm::vec3 lightPositionStar = glm::vec3(.0f, 7.0f, .0f);	
	glUniform3f(glGetUniformLocation(programID, "LightPositionStar"), lightPositionStar.x, lightPositionStar.y, lightPositionStar.z);
	glm::mat4 Save = Model;
	Position p = getPosition();
	Model = glm::translate(Model, glm::vec3(p.getX(), p.getY(), p.getZ()));
	m_renderer.sendMVP(Model);
	RenderedObject::drawVertices(Model);
	Model = Save;
}

// Destructor
Star::~Star()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}
