#include "Renderer.h"

Renderer::Renderer(GLuint progID, glm::mat4 proj, glm::mat4 view)
{
	programID = progID;
	Projection = proj;
	View = view;
}

Renderer::~Renderer()
{
}

/** Holds the model view projection matrix.
*
*	@param &Model	Memory address of the model.
*/
void Renderer::sendMVP(glm::mat4 &Model)
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model;
	// Send our transformation to the currently bound shader, 
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);
}
