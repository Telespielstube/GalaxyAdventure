#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

class RenderedObject
{
public:
	RenderedObject();
	virtual ~RenderedObject();
	virtual void draw();
protected:
	GLuint VertexArrayID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;
};

