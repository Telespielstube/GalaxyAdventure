#include "RenderedObject.h"

RenderedObject::RenderedObject()
{
}


RenderedObject::~RenderedObject()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}

void RenderedObject::draw()
{
	glBindVertexArray(VertexArrayID);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
