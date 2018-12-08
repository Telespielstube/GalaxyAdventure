#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model;
	// Send our transformation to the currently bound shader, 
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);

}

/** Aligns the ship to the right position on screen.
*/
void alignShipOnScreen()
{
	Save = Model;
	Model = glm::translate(Model, glm::vec3(.0f, -12.0f, .0f));
	sendMVP();
	spaceShip->draw();
	Model = Save;
}
/** Aligns the ship to the right position on screen.
*
*/
void alignGateOnScreen()
{
	float scaleFactor = 3.0f;
	float angleX = -45.0f;
	float angleY = 90.0f;
	Save = Model;
	Model = glm::scale(Model, glm::vec3(1.0f * scaleFactor, 1.0f * scaleFactor, 1.0f * scaleFactor));
	Model = glm::translate(Model, glm::vec3(.0f, -1.0f, .0f));
	Model = glm::rotate(Model, angleX, glm::vec3(1.0f, .0f, .0f));
	Model = glm::rotate(Model, angleY, glm::vec3(.0f, 1.0f, .0f));
	sendMVP();
	gate->draw();
	Model = Save;
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
	
	//Create objects
	spaceShip = new Spaceship("Ship.obj");
	gate = new Gate("Gate.obj");
	Controls controls;

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

	do 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float spaceShipMovement = controls.moveSpaceship(window);
		Model = glm::translate(Model, glm::vec3(spaceShipMovement, 0.0, 0.0));

		alignShipOnScreen();
		alignGateOnScreen();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	
	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}

