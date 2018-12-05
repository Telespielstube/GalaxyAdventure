#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> 
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

class Spaceship
{
	GLuint VertexArrayID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vertexbuffer;
	//GLuint normalbuffer;
	//GLuint uvbuffer;

public:
	//
	Spaceship();
	
	//
	void drawSpaceShip();
	~Spaceship();
};

