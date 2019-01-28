#pragma once

#include <glm\gtc\matrix_transform.hpp>
#include <GL/glew.h>

/*	Renderer

	@autor
*/
class Renderer
{
public:
	Renderer(GLuint progID, glm::mat4 proj, glm::mat4 view);
	~Renderer();

	void sendMVP(glm::mat4 & Model);

protected:
	GLuint programID;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 MVP;
	glm::mat4 Save;

};

