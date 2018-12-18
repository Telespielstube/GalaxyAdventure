#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <time.h>
#include "Renderer.h"
#include "Shader.h"
#include "Spaceship.h"
#include "Texture.h"
#include "Controls.h"
#include "Gate.h"
#include "RandomNumber.h"
#include "cube.h"

// Global variables
GLFWwindow *window;
GLuint programID;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;

//Initializes the OpenGL library GLFW.
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

/** Creates the main windows where the game happens.
*
*	@param	width		width of the window.
*	@param	height		height of the window.
*	@param	title		title of the window.
*	@param	xPosition	xPosition on screen.
*	@param	yPosition	yPosition on screen.
*
*/
GLFWwindow *createMainWindow(int width, int height, const char *title, int xPosition, int yPosition)
{
	window = glfwCreateWindow(width, height, title, /*glfwGetPrimaryMonitor()*/ NULL, NULL);
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

bool colDetection(ColBox box1, ColBox box2) {
	if (box1.getPosX() + box1.getColX() >= box2.getPosX() && box2.getPosX() + box2.getColX() >= box1.getPosX() &&
		box1.getPosY() + box1.getColY() >= box2.getPosY() && box2.getPosY() + box2.getColY() >= box1.getPosY() &&
		box1.getPosZ() + box1.getColZ() >= box2.getPosZ() && box2.getPosZ() + box2.getColZ() >= box1.getPosZ()) {
		//std::cout << box1.getPosX()<< ">=" << box2.getPosX() << std::endl;
		return true;
	}
	else {
		return false;
	}

}

int main()
{
	glewExperimental = true;
	if (!initializeGLFW()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	window = createMainWindow(1800, 900, "GalaxyAdventure", 100, 100);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	


	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	//GLuint Texture = loadBMP_custom("shipTexture.bmp");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	glUseProgram(programID);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(80.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix		
	View = glm::lookAt(
		glm::vec3(0, 20, 20),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	//Create objects on stack   
	Renderer modelRenderer(programID, Projection, View);
	Spaceship spaceShip("Ship.obj", modelRenderer);
	Gate *gate;
	RandomNumber randomNumber;
	Controls controls;

	// Array of gates and random positions. 
	randomNumber.initializeGenerator();
	float newPosition = -2.5f;
	float max = .0f;
	float min = .0f;
	std::vector<Gate*> gateList;

	for (int i = 0; i < 5; i++)
	{
		max = 4.0f - ((float)rand()) / (float)RAND_MAX;
		min = -4.0f + ((float)rand()) / (float)RAND_MAX;
		gate = new Gate("Gate.obj", modelRenderer);
		gateList.push_back(gate);
		
		/*
		// Random Gate Position
		gate->setPosition((randomNumber.generateRandomNumber(max, min)),
						(randomNumber.generateRandomNumber(max, min)),
						newPosition);
		*/

		// Für Testzwecke Gates in einer reihe
		gate->setPosition(0, 0 ,0 - (i * 3));

		newPosition -= 5.0f;
		gate->setXAngle(-5.0f); // rotates gate
		gate->setYAngle(90.0f); // rotates gate

		// Erzeugt die KollisionsBox um das Gate
		gate->setColBox(ColBox(gate->getXPosition()*gate->getScaleF()-1, gate->getYPosition()*gate->getScaleF()-1.5, gate->getZPosition()*gate->getScaleF(), 2.5 * gate->getScaleF(), 2 * gate->getScaleF(), 0.5 * gate->getScaleF()));
		//std::cout << gate->getColBox().getPosX() << " " << gate->getColBox().getPosY() << " " << gate->getColBox().getPosZ() << std::endl;
		
	}
	
	spaceShip.setPosition(.0f, .0f, 13.5f);

	// Collisions Distanz
	float colDX = 7.0f;
	float colDZ = 5.0f;
	float colDY = 5.0f;
	float colL = 4.2f;

	ColBox *box2 = new ColBox{ 0,0,0,10,10,4 };
	ColBox *box3 = new ColBox{ 2,0,5,2,2,2 };
	
	//Game loop
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float spaceShipOnX = controls.moveSpaceshipOnX(window);
		float spaceShipOnY = controls.moveSpaceshipOnY(window);
		float spaceShipOnZ = controls.moveSpaceshipOnZ(window);

		//Light source
		glm::vec4 lightPositionWorld = Model * glm::vec4(0, 8.0, -2.0f, 1);
		glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPositionWorld.x, lightPositionWorld.y, lightPositionWorld.z);
		

		//schreibt die Akktuelle Position des Schiffes auf die Konsole
		//std::cout << spaceShip.getXPosition() << " " << spaceShip.getYPosition() << " " << spaceShip.getZPosition() << std::endl;
		
		
		
		bool collision = false;

		// Geht die Gates durch
		for (int i = 0; i < 5; i++)
		{
			Gate *g(gateList.at(i));
			ColBox b = g->getColBox();			
			// Collisionsdetection
			if (colDetection(gateList.at(i)->getColBox(), ColBox{ spaceShip.getXPosition() + spaceShipOnX,spaceShip.getYPosition() + spaceShipOnY, spaceShip.getZPosition() + spaceShipOnZ,1,1,1 })) {
				collision = true;				
			}			
			// Zeichnet Gate
			g->draw(Model);
		}
		
		// Wenn keine Kollision = Schiff bewegen
		if (!collision) {
			spaceShip.setPosition((spaceShip.getXPosition() + spaceShipOnX), (spaceShip.getYPosition() + spaceShipOnY), (spaceShip.getZPosition() + spaceShipOnZ));
		}

		// Zeichnet Schiff
		spaceShip.draw(Model);
		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}

