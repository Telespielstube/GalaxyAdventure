#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include "Renderer.h"

class RenderedObject
{
public:
	RenderedObject(const char *filename, Renderer& renderer);
	virtual ~RenderedObject();
	virtual void draw(glm::mat4 &Model);

	virtual void setPosition(float x, float y, float z);
	float getXPosition() { return xPosition; }
	float getYPosition() { return yPosition; }
	float getPosition() { return zPosition; }
protected:
	void sendMVP(glm::mat4 &Model);
	Renderer &m_renderer;

	GLuint VertexArrayID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;

	float xPosition;
	float yPosition;
	float zPosition;
};
