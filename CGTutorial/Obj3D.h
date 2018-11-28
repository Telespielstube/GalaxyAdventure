#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
// Include GLM
#include <glm/glm.hpp> 
#include <vector>
#include <glm\gtc\matrix_transform.hpp>



class Obj3D
{
	GLuint VertexArrayID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint uvbuffer;

public:
	// Constructor
	Obj3D(const char *fileName);

	void draw();


	Obj3D();
	~Obj3D();
};

