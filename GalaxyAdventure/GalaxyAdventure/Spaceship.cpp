#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"
#include "ColBox.h"




/** Constructor
*
*	@param	filename	path to the object file.
*	@param	renderer	holds the 3 matrices Model, View, Perspective information.
*
*/
Spaceship::Spaceship(const char *filename, Renderer &renderer) : RenderedObject(filename, renderer), box1(5, 5, 5)
{

}

/** Destructor
*/
Spaceship::~Spaceship() {}


void Spaceship::draw(glm::mat4 & Model)
{

	glm::mat4 Save = Model;
	Model = glm::translate(Model, glm::vec3(xPosition, yPosition, zPosition));
	m_renderer.sendMVP(Model);
	RenderedObject::drawVertices(Model);
	Model = Save;
}


