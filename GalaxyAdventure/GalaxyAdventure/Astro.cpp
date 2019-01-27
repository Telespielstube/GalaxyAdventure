#include "Astro.h"
#include "objloader.h"




Astro::Astro(const char * filename, Renderer & renderer, GLuint gateTexture, GLuint TextureID, float scaleF) : RenderedObject(filename, renderer)
{
	texture = gateTexture;
	textureID = TextureID;	
	scaleFactor = scaleF;

	addColCicle(new ColCicle(Position(0.0f, 0.0f, 0.0f), 1.25f, 1.68f));

}

Astro::~Astro()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
}

void Astro::draw(glm::mat4 & Model, GLuint programID)
{
	glActiveTexture(GL_TEXTURE0);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glUniform1i(textureID, 0);	
	glm::vec3 lightPositionAstro = glm::vec3(.0, 0.0, .0);
	glUniform3f(glGetUniformLocation(programID, "LightPositionAstro"), lightPositionAstro.x, lightPositionAstro.y, lightPositionAstro.z);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glm::mat4 Save = Model;
	Position p = getPosition();
	Model = glm::translate(Model, glm::vec3(p.getX(), p.getY(), p.getZ()));
	Model = glm::rotate(Model, p.getAngleX(), glm::vec3(1.0f, .0f, .0f));
	Model = glm::rotate(Model, p.getAngleY(), glm::vec3(.0f, 1.0f, .0f));
	Model = glm::rotate(Model, p.getAngleZ(), glm::vec3(.0f, 0.0f, 1.0f));
	Model = glm::scale(Model, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
	//std::cout << p.getAngleX() << " " << p.getAngleY() << " " <<  std::endl;
	m_renderer.sendMVP(Model);
	RenderedObject::drawVertices(Model);
	Model = Save;
}

float Astro::getScaleF()
{
	return scaleFactor;
}

void Astro::setDirection(float x, float y, float z)
{
	dX = x;
	dY = y;
	dZ = z;
}

void Astro::setScaleF(float s)
{
	scaleFactor = s;
}
