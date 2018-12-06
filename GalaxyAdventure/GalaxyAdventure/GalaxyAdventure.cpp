#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Spaceship.h"
#include "Texture.h"
#include "Control.h"

GLFWwindow* window;

GLuint programID;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;
 
void sendMVP()
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model;
	// Send our transformation to the currently bound shader, 
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);

}


int main() 
{
	// Initialise GLFW
	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
	
	window = glfwCreateWindow(1366, 768, "Galaxy Adventure", NULL, NULL);
	//Sets the postion for the window
	glfwSetWindowPos(window, 120, 120);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	
	
	GLuint Texture = loadBMP_custom("shiptexture.bmp");
	
	//Create objects
	Spaceship* spaceShip = new Spaceship("Ship.obj");
	Control control;
	//Create gate object here.
	
	do {
		glDisable(GL_CULL_FACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		float spaceShipMovement = control.moveSpaceship();
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		Model = glm::translate(Model, glm::vec3(spaceShipMovement, 0.0, 0.0));
		
		// Camera matrix
		View = glm::lookAt(
			glm::vec3(0, 18, 20), // Camera is at (4,3,-3), in World Space
			glm::vec3(0, 8, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);

		sendMVP();
		//Draw object
		spaceShip->drawSpaceShip();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	
	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}

