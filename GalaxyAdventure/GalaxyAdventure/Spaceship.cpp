#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <time.h>
#include "Spaceship.h"
#include "objloader.h"
#include "ColBox.h"
#include "objects.hpp"
#include "Controls.h"


/** Constructor
*
*	@param	filename		path to the object file.
*	@param	renderer		holds the 3 matrices Model, View, Perspective information.
*	@param  ShipTexture		Texture of the ship.
*	@param	TextureID		id for the texture of the ship..
*
*/
Spaceship::Spaceship(const char *filename, Renderer &renderer, GLuint shipTexture, GLuint TextureID) : RenderedObject(filename, renderer), box1(-1,0,-2, 2, 2, 5)
{
	texture = shipTexture;
	textureID = TextureID;
}

/** Draws the starship on screen.
*
*	@param	Model			the scene in which the game takes place
*	@param programID		an id for the current application
*
*/
void Spaceship::draw(glm::mat4 &Model, GLuint programID)
{	
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
	glm::vec3 lightPositionSpaceShip = glm::vec3(.0, 7.0, .0);
	glUniform3f(glGetUniformLocation(programID, "LightPositionSpaceShip"), lightPositionSpaceShip.x, lightPositionSpaceShip.y, lightPositionSpaceShip.z);
	glm::mat4 Save = Model;
	Position p = getPosition();
	Model = glm::translate(Model, glm::vec3(p.getX(), p.getY(), p.getZ()));
	m_renderer.sendMVP(Model);	
	RenderedObject::drawVertices(Model);
	Model = Save;
}

/** Destructor
*/
Spaceship::~Spaceship() {}
