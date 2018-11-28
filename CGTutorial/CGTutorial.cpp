// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Obj3D.h"
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Achtung, die OpenGL-Tutorials nutzen glfw 2.7, glfw kommt mit einem veränderten API schon in der Version 3 

// Befindet sich bei den OpenGL-Tutorials unter "common"
#include "shader.hpp"

#include "texture.hpp"

// Wuerfel und Kugel
#include "objects.hpp"
#include "objloader.hpp"
#define UEBUNG1 /* feste Rotation */


float AngleX = .0f;
float AngleY= .0f;
float AngleZ = .0f;
float roboAngleX = .0f;
float roboAngleY = .0f;
float roboAngleZ = .0f;


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;

	case GLFW_KEY_UP:
		AngleX += 10.0f;
		break;

	case GLFW_KEY_DOWN:
		AngleX -= 10.0f;
		break;

	case GLFW_KEY_RIGHT:
		AngleY += 10.0f;	
		break;

	case GLFW_KEY_LEFT:
		AngleY -= 10.0f;
		break;

	case GLFW_KEY_Z:
		AngleZ += 10.0f;
		break;

	case GLFW_KEY_U:
		AngleZ -= 10.0f;
		break;
	//Roboter Section navigation
	case GLFW_KEY_W:
		roboAngleX -= 10.0f;
		break;

	case GLFW_KEY_S:
		roboAngleX += 10.0f;
		break;

	case GLFW_KEY_Q:
		roboAngleY -= 10.0f;
		break;

	case GLFW_KEY_A:
		roboAngleY += 10.0f;
		break;

	case GLFW_KEY_E:
		roboAngleX -= 10.0f;
		break;

	case GLFW_KEY_D:
		roboAngleX += 10.0f;
		break;
	default:
		break;
	}
}


// Diese Drei Matrizen global (Singleton-Muster), damit sie jederzeit modifiziert und
// an die Grafikkarte geschickt werden koennen
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
//Teapot translation



GLuint programID;



void sendMVP()
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; 
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform, konstant fuer alle Eckpunkte
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);

}

// Koordinatensystem zeichnen
void drawCoordinateSystem() 
{
	glm::mat4 Save = Model;

		// 1. line
		Model = glm::scale(Model, glm::vec3(10.0, 0.02, 0.02));
		sendMVP();
		drawCube();
		Model = Save;
		//2. line
		Model = glm::scale(Model, glm::vec3(0.02, 20.0, 0.02));
		sendMVP();
		drawCube();
		Model = Save;
		// 3. line
		Model = glm::scale(Model, glm::vec3(0.02, 0.02, 20.0));
		sendMVP();
		drawCube();
		Model = Save;
}


// Roboterarm zeichnen
void drawRoboSec(float height)
{
	glm::mat4 Save = Model;
	Model = glm::translate(Model, glm::vec3(0, height / 2, 0));
	Model = glm::scale(Model, glm::vec3(height / 6, height / 2, height / 6));
	sendMVP();
	drawSphere(10, 10);
	Model = Save;
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	// Fehler werden auf stderr ausgegeben, s. o.
	glfwSetErrorCallback(error_callback);

	// Open a window and create its OpenGL context
	// glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen
	GLFWwindow* window = glfwCreateWindow(1024, // Breite
										  768,  // Hoehe
										  "CG - Tutorial", // Ueberschrift
										  NULL,  // windowed mode
										  NULL); // shared windoe

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make the window's context current (wird nicht automatisch gemacht)
    glfwMakeContextCurrent(window);

	// Initialize GLEW
	// GLEW ermöglicht Zugriff auf OpenGL-API > 1.1
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Auf Keyboard-Events reagieren
	glfwSetKeyCallback(window, key_callback);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create and compile our GLSL program from the shaders
	//programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");

	// Shader auch benutzen !
	glUseProgram(programID);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/**
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Teapot-object
	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("teapot.obj", vertices, uvs, normals);

	// Jedes Objekt eigenem VAO zuordnen, damit mehrere Objekte moeglich sind
	// VAOs sind Container fuer mehrere Buffer, die zusammen gesetzt werden sollen.
	GLuint VertexArrayIDTeapot;
	glGenVertexArrays(1, &VertexArrayIDTeapot);
	glBindVertexArray(VertexArrayIDTeapot);

	// Ein ArrayBuffer speichert Daten zu Eckpunkten (hier xyz bzw. Position)
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer); // Kennung erhalten
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // Daten zur Kennung definieren
												 // Buffer zugreifbar für die Shader machen
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Erst nach glEnableVertexAttribArray kann DrawArrays auf die Daten zugreifen...
	glEnableVertexAttribArray(0); // siehe layout im vertex shader: location = 0 
	glVertexAttribPointer(0,  // location = 0 
		3,  // Datenformat vec3: 3 floats fuer xyz 
		GL_FLOAT,
		GL_FALSE, // Fixedpoint data normalisieren ?
		0, // Eckpunkte direkt hintereinander gespeichert
		(void*)0); // abweichender Datenanfang ? 
		
	GLuint normalbuffer; // Hier alles analog für Normalen in location == 2
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2); // siehe layout im vertex shader 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint uvbuffer; // Hier alles analog für Texturkoordinaten in location == 1 (2 floats u und v!)
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); // siehe layout im vertex shader 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	*/
	// Load the texture
	GLuint Texture = loadBMP_custom("mandrill.bmp");

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(glGetUniformLocation(programID, "myTextureSampler"), 0);

	//Create object teapot and draw it
	Obj3D* teapot = new Obj3D("teapot.obj");
	
	



	// Eventloop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the screen
		// glClear(GL_COLOR_BUFFER_BIT);	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		
		// Camera matrix
		View = glm::lookAt(glm::vec3(0,0,-10), // Camera is at (0,0,-5), in World Space
						   glm::vec3(0,0,0),  // and looks at the origin
						   glm::vec3(0,1,0)); // Head is up (set to 0,-1,0 to look upside-down)
		
		// Model matrix : an identity matrix (model will be at the origin)
		Model = glm::mat4(1.0f);
		Model = glm::rotate(Model, AngleX, glm::vec3(1.0f, .0f, .0f));
		Model = glm::rotate(Model, AngleY, glm::vec3(.0f, 1.0f, .0f));
		Model = glm::rotate(Model, AngleZ, glm::vec3(.0f, .0f, 1.0f));
		
		// Save State der Rotation
		glm::mat4 Save = Model;
		//  Teapot tranlate
		Model = glm::translate(Model, glm::vec3(1.5f, 0.0, 0.0));

		//drawWireCube();
		//drawCube();
		
		// teapot scale down
		Model = glm::scale(Model, glm::vec3(1.0 / 1000.0, 1.0 / 1000.0, 1.0 / 1000.0));
		//Lightning for teapot object
		glm::vec3 lightPos = glm::vec3(4, 4, -4);

		//glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);

		sendMVP();
		// Draw Teapot 
		//glBindVertexArray(VertexArrayID);
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		teapot->draw();
		
		// Draw and scale sphere
		Model = Save;
		Model = glm::scale(Model, glm::vec3(0.5, 0.5, 0.5));
		sendMVP();
		
		//drawWireCube();
		//drawSphere(10, 10);
		drawCoordinateSystem();
		
		// Robot segments and lightning
		drawRoboSec(2);
		Model = glm::translate(Model, glm::vec3(0, 1.9, 0));
		Model = glm::rotate(Model, roboAngleX, glm::vec3(1.0f, .0f, .0f));
		Model = glm::rotate(Model, roboAngleY, glm::vec3(.0f, 1.0f, .0f));
		Model = glm::rotate(Model, roboAngleZ, glm::vec3(.0f, .0f, 1.0f));
		drawRoboSec(1.5);
		Model = glm::translate(Model, glm::vec3(0, 1.4, 0));
		Model = glm::rotate(Model, roboAngleX, glm::vec3(1.0f, .0f, .0f));
		Model = glm::rotate(Model, roboAngleY, glm::vec3(.0f, 1.0f, .0f));
		Model = glm::rotate(Model, roboAngleZ, glm::vec3(.0f, .0f, 1.0f)); 
		drawRoboSec(1.3);
		Model = glm::translate(Model, glm::vec3(0, 1.4, 0));
		Model = glm::rotate(Model, roboAngleX, glm::vec3(1.0f, .0f, .0f));
		Model = glm::rotate(Model, roboAngleY, glm::vec3(.0f, 1.0f, .0f));
		Model = glm::rotate(Model, roboAngleZ, glm::vec3(.0f, .0f, 1.0f));
		
		// 
		glm::vec4 lightPositionWorld =  Model * glm::vec4(0, 0.3, 0, 1);
		glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPositionWorld.x, lightPositionWorld.y, lightPositionWorld.z);

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll for and process events 
        glfwPollEvents();
	} 


	glDeleteTextures(1, &Texture);

	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}



