#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include "Renderer.h"
#include "Position.h"

class RenderedObject
{
public:
	RenderedObject(const char *filename, Renderer &renderer);
	virtual ~RenderedObject();
	virtual void drawVertices(glm::mat4 &Model);
	virtual void setPosition(float x, float y, float z);
	Position getPosition();	
	virtual void setXAngle(float x);
	virtual void setYAngle(float y);
	

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

	GLuint texture;
	GLuint textureID;

	float xAngle;
	float yAngle;

private:
	Position position;	
	
};
