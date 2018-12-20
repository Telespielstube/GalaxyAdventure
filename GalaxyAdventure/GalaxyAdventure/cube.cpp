#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "cube.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>



GLuint VertexArrayIDWireCube;

cube::cube(float posX, float posY, float posZ, float disX, float disY, float disZ)
{
	x = posX;
	y = posY;
	z = posZ;
	cX = disX;
	cY = disY;
	cZ = disZ;
	VertexArrayIDWireCube = 0;
}

void cube::drawCube(){	
	
	if (!VertexArrayIDWireCube)
	{
		// Vertexarrays kapseln ab OpenGL3 Eckpunkte, Texturen und Normalen
		glGenVertexArrays(1, &VertexArrayIDWireCube);
		glBindVertexArray(VertexArrayIDWireCube);
		// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
		// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
		GLfloat g_vertex_buffer_data[] = {
			x,y,z, x,y, cZ + z,
			x,y + cY,z, x, cY + y, cZ + z,
			x + cX, y, z,  cX + x, y, cZ + z,
			x + cX, y + cY, z,  x + cX, y + cY, cZ + z,
			x, y, z, x, cY + y, z,
			x, y, z + cZ, x, cY + y, cZ + z,
			x + cX, y, z,  cX + x, cY + y, z,
			x + cX, y, z + cZ,  cX + x, cY + y, cZ + z,
			x, y, z,  cX + x, y, z,
			x, y, cZ + z,  cX + x, y, cZ + z,
			x, y + cY, z,  cX + x, cY + y, z,
			x, cY + y, cZ + z,  cX + x, cY + y, cZ + z
		};

		// Vertexbuffer-Daten z.B. auf Grafikkarte kopieren
		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		// Erklären wie die Vertex-Daten zu benutzen sind
		glEnableVertexAttribArray(0); // Kein Disable ausführen !
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindVertexArray(0);
	}
	glBindVertexArray(VertexArrayIDWireCube);
	glDrawArrays(GL_LINES, 0, 24); // 12 Linien haben 24 Punkte
}


cube::~cube()
{
}



float cube::getColX()
{
	return cX;
}

float cube::getColY()
{
	return cY;
}

float cube::getColZ()
{
	return cZ;
}

float cube::getPosX()
{
	return x;
}

float cube::getPosY()
{
	return y;
}

float cube::getPosZ()
{
	return z;
}
