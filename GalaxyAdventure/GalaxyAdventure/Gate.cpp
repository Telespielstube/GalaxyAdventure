#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Spaceship.h"
#include "objloader.h"
#include "Gate.h"

GLuint GateVertexArrayID;

std::vector<glm::vec3> gateVertices;
std::vector<glm::vec2> gateUvs;
std::vector<glm::vec3> gateNormals;

GLuint gateVertexBuffer;
GLuint gateNormalBuffer;
GLuint gateUvBuffer;

/** Funtion to read the data from the file and passing the data to the vertexshader and fragmentshader.
*
*	@param	filename	path of the obj. file.
*
*/
Gate::Gate(const char *filename)
{
	bool object = loadObject(filename, gateVertices, gateUvs, gateNormals);

	glGenVertexArrays(1, &GateVertexArrayID);
	glBindVertexArray(GateVertexArrayID);

	glGenBuffers(1, &gateVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gateVertexBuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, gateVertices.size() * sizeof(glm::vec3), &gateVertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, gateVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glGenBuffers(1, &gateNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gateNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, gateNormals.size() * sizeof(glm::vec3), &gateNormals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2); // siehe layout im vertex shader 
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);


	glGenBuffers(1, &gateUvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gateUvBuffer);
	glBufferData(GL_ARRAY_BUFFER, gateUvs.size() * sizeof(glm::vec2), &gateUvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); // siehe layout im vertex shader 
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);
}

/** Draws the gate on the screen.
*
*/
void Gate::drawGate()
{
	glBindVertexArray(GateVertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, gateVertices.size());
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
	glDeleteBuffers(1, &gateVertexBuffer);
	glDeleteBuffers(1, &gateUvBuffer);
	glDeleteBuffers(1, &gateNormalBuffer);
}
