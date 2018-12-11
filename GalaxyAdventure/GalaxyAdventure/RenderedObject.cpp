#include "RenderedObject.h"
#include "objloader.h"


/** Constructor to read the data from the file and passing the data to the vertexshader and fragmentshader
*
*	@param	filename	path of the obj. file.
*/
RenderedObject::RenderedObject(const char *filename, Renderer &renderer) : m_renderer(renderer)
{
    xPosition = 0.0f;
	yPosition = 0.0f;
	zPosition = 0.0f;
	xAngle = .0f;

	bool object = loadObject(filename, vertices, uvs, normals);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2); // siehe layout im vertex shader 
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); // siehe layout im vertex shader 
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0);
}

/** Draws the vertices on screen.
*
*/
void RenderedObject::drawVertices(glm::mat4 &Model)
{
	glBindVertexArray(VertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

/** Sets a specific position of the object.
*	
*	@param	x	holds the x coordinate.
*	@param	y	holds the y coordinate.
*	@param	z	holds the z coordinate.
*/
void RenderedObject::setPosition(float x, float y, float z)
{
	xPosition = x;
	yPosition = y;
	zPosition = z;
}

/** Get function for x Position of object.
*
*/
float RenderedObject::getXPosition()
{
	return xPosition;
}

/** Get function for y Position of object.
*
*/
float RenderedObject::getYPosition()
{
	return yPosition;
}

/** Get function for z Position of object.
*
*/
float RenderedObject::getZPosition()
{
	return zPosition;
}

void RenderedObject::setXAngle(float x)
{
	xAngle = x;
}

void RenderedObject::setYAngle(float y)
{
	yAngle = y;
}












/** Destructor
*
*/
RenderedObject::~RenderedObject()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}