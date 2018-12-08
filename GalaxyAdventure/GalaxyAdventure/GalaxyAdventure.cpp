#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Shader.h"
#include "Spaceship.h"
#include "Texture.h"
#include "Controls.h"
#include "Gate.h"

GLFWwindow *window;
Spaceship *spaceShip;
Gate *gate;
GLuint programID;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;
glm::mat4 Save;
 

void sendMVP()
{

}

/** Aligns the ship to the right position on screen.
*/
void alignShipOnScreen()
{
	Save = Model;
	Model = glm::translate(Model, glm::vec3(.0f, -12.0f, .0f));
	sendMVP();
	spaceShip->draw(Model);
	Model = Save;
}
/** Aligns the ship to the right position on screen.
*
*/
void alignGateOnScreen()
{

}

bool initializeGLFW()
{
	if (!glfwInit())
	{
		return false; 
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return true;
}

GLFWwindow *createMainWindow(int width, int height, const char *title, int xPosition, int yPosition)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return NULL;
	}

	//Sets the postion for the window
	glfwSetWindowPos(window, xPosition, yPosition);
    glfwMakeContextCurrent(window); //

	return window;
}

int main() 
{
	glewExperimental = true; 
	if (!initializeGLFW()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	
	window = createMainWindow(1366, 768, "GalaxyAdventure", 120, 120);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint Texture = loadBMP_custom("shiptexture.bmp");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	glUseProgram(programID);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	View = glm::lookAt(
		glm::vec3(0, 18, 20),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	Renderer myRenderer(programID, Projection, View);

	//Create objects
	spaceShip = new Spaceship("Ship.obj", myRenderer);
	gate = new Gate("Gate.obj", myRenderer);
	gate->setPosition(0.0f, -1.0f, 0.0f);
	Controls controls;
	do 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float spaceShipMovement = controls.moveSpaceship(window);
		spaceShip->setPosition(spaceShip->getXPosition() + spaceShipMovement, -12.0f, 0.0f);
		spaceShip->draw(Model);
		gate->draw(Model);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	
	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}

