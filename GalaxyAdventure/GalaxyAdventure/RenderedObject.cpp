#include "RenderedObject.h"
#include "objloader.h"


/** Constructor to read the data from the file and passing the data to the vertexshader and fragmentshader
*
*	@param	filename	path of the obj. file.
*	@param	Renderer	Memory address of the Model, view, projection matrix.
*
*/
RenderedObject::RenderedObject(const char *filename, Renderer &renderer) : m_renderer(renderer)
{
	position.setPosition(Position(0, 0, 0));    
	

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
*	@param	Model	Memory address of the Model matrix.
*
*/
void RenderedObject::drawVertices(glm::mat4 &Model)
{
	glBindVertexArray(VertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

/** Returns the position of an object.
*
*	@return position of an object.
*/
Position RenderedObject::getPosition()
{
	return position;
}

/** Returns the collision box.
*
*	@return a vector(array) of collision boxes.
*
*/
std::vector <ColBox*> RenderedObject::getColBox()
{
	return colBoxList;
}

/** Returns the collision circle.
*
*	@return a vector(array) of collision circles.
*
*/
std::vector<ColCicle*> RenderedObject::getColCicle()
{
	return colCicleList;
}

/** Adds a collision box.
*
*	@param	*b	pointer to a collision box.
*
*/
void RenderedObject::addColBox(ColBox *b)
{
	colBoxList.push_back(b);
}

/** Adds a collision box.
*
*	@param *c	pointer to a collion circle.
*
*/
void RenderedObject::addColCicle(ColCicle * c)
{
	colCicleList.push_back(c);
}

/** Sets a specific position of the object.
*	
*	@param	p	holds the Position data.
*
*/
void RenderedObject::setPosition(Position p)
{
	position.setPosition(p.getX(), p.getY(), p.getZ(), p.getAngleX(), p.getAngleY(), p.getAngleZ());	
	
}

// Destructor
RenderedObject::~RenderedObject()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}