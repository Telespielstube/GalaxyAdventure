#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"




/** Funtion to read the data from the file and passing the data to the vertexshader and fragmentshader
*	@param	filename	path of the obj. file.
*/
Spaceship::Spaceship(const char *filename, Renderer &renderer) : RenderedObject(filename, renderer)
{
}

Spaceship::~Spaceship()
{
}

void Spaceship::draw(glm::mat4 & Model)
{
	glm::mat4 Save = Model;
	Model = glm::translate(Model, glm::vec3(xPosition, yPosition, zPosition));
	m_renderer.sendMVP(Model);
	RenderedObject::draw(Model);
	Model = Save;
}

