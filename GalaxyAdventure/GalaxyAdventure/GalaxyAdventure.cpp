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
#include "WindowInit.h"

GLuint programID;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
float angleX;
float angleY;
float angleZ;

/** Kollisionsdetection
*
*	Prüft zwei übergebene Kollisionsboxen ob sie sich berühren wenn ja wird true zurückgegben.
*/
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
	WindowInit windowInit;
	glewExperimental = true;
	if (!windowInit.initializeGLFW()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	GLFWwindow* window = windowInit.createMainWindow(1800, 900, "GalaxyAdventure", 100, 100);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0);
	
	// Loads shaders and textures.
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint shipTexture = loadBMP("shipTexture.bmp");
	GLuint TextureID = glGetUniformLocation(programID, "objectTexture");
	GLuint gateTexture = loadBMP("gateTexture.bmp");
	GLuint gateTextureID = glGetUniformLocation(programID, "objectTexture");
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	glUseProgram(programID);
	glMatrixMode(GL_MODELVIEW);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(80.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera position
	glm::vec3 cameraPos = glm::vec3(0, 7, 12);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1);
	glm::vec3 cameraUp = glm::vec3(0.0f, 3.0f, 0.0f);
	View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	//Create objects on stack   
	Renderer modelRenderer(programID, Projection, View);
	Spaceship spaceShip("Ship.obj", modelRenderer, shipTexture, TextureID);
	Gate *gate;
	RandomNumber randomNumber;
	Controls controls;

	// Array of gates and random positions. 
	randomNumber.initializeGenerator();
	float max = .0f;
	float min = .0f;
	std::vector<Gate*> gateList;

	for (int i = 0; i < 5; i++)
	{
		max = 4.0f - ((float)rand()) / (float)RAND_MAX;
		min = -4.0f + ((float)rand()) / (float)RAND_MAX;
		gate = new Gate("Gate.obj", modelRenderer, gateTexture, gateTextureID);
		gateList.push_back(gate);
		
		/*
		// Random Gate Position
		gate->setPosition((randomNumber.generateRandomNumber(max, min)),
						(randomNumber.generateRandomNumber(max, min)),
						newPosition);
		*/

		// Für Testzwecke Gates in einer reihe
		gate->setPosition(0, 0 ,-10 - (i * 14));

		gate->setXAngle(-5.0f); 
		gate->setYAngle(90.0f); 

		// Erzeugt die KollisionsBox um das Gate
		// Erste KollisionsBox ist über das Ganze Gate
		float s = 1.08;
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 5 * s, gate->getYPosition()*gate->getScaleF() - 5 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 10 * gate->getScaleF(), 10 * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 1.5* s, gate->getYPosition()*gate->getScaleF() - 4 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 3 * s * gate->getScaleF(), 1.0f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 3 * s, gate->getYPosition()*gate->getScaleF() - 3.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1.5* s * gate->getScaleF(), 1.0f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 1.5* s, gate->getYPosition()*gate->getScaleF() - 3.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1.5f* s * gate->getScaleF(), 1.0f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 3.5* s, gate->getYPosition()*gate->getScaleF() - 2.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 1.0f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 2.5* s, gate->getYPosition()*gate->getScaleF() - 2.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 1.0f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 4 * s, gate->getYPosition()*gate->getScaleF() - 1.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 0.5f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 3 * s, gate->getYPosition()*gate->getScaleF() - 1.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 0.5f* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 4 * s, gate->getYPosition()*gate->getScaleF() - 1 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 2 * s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 3.5* s, gate->getYPosition()*gate->getScaleF() - 1 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 0.5* s * gate->getScaleF(), 2 * s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 4 * s, gate->getYPosition()*gate->getScaleF() + 1 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s *gate->getScaleF(), 0.5 * s* gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 3 * s, gate->getYPosition()*gate->getScaleF() +1 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s* gate->getScaleF(), 0.5* s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 3.5* s, gate->getYPosition()*gate->getScaleF() +1.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 1 * s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 2.5* s, gate->getYPosition()*gate->getScaleF() + 1.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1 * s * gate->getScaleF(), 1 * s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 3 * s, gate->getYPosition()*gate->getScaleF() + 2.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1.5* s * gate->getScaleF(), 1 * s* gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() + 1.5* s, gate->getYPosition()*gate->getScaleF() + 2.5* s, gate->getZPosition()*gate->getScaleF() - 3.2, 1.5* s * gate->getScaleF(), 1 * s * gate->getScaleF(), 4 * gate->getScaleF()));
		gate->addColBox(new ColBox(gate->getXPosition()*gate->getScaleF() - 1.5* s, gate->getYPosition()*gate->getScaleF() + 3 * s, gate->getZPosition()*gate->getScaleF() - 3.2, 3 * s * gate->getScaleF(), 1.0f* s * gate->getScaleF(), 4 * gate->getScaleF()));
				
		//std::cout << gate->getZPosition()*gate->getScaleF() << std::endl;
		
	}

	spaceShip.setPosition(.0f, .0f, 0.0f);
	
	//Game loop
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float spaceShipOnX = controls.moveSpaceshipOnX(window);
		float spaceShipOnY = controls.moveSpaceshipOnY(window);
		float spaceShipOnZ = controls.moveSpaceshipOnZ(window);
		float angleX = controls.CamOnX(window);
		float angleY = controls.CamOnY(window);

		glm::mat4 Save = Model;
		Model = glm::translate(Model, glm::vec3(1.5, 0, 0));
	
		modelRenderer.sendMVP(Model);	
		
		bool collision = false;
		int objID = -1;

		// Kollisionsboxen für das Schiff. 
		// TODO. vll auch eine Main Kollisionsbox erstellen über das ganze Schiff.
		ColBox *colShip = new ColBox{ spaceShip.getXPosition() + spaceShipOnX - 0.7f, spaceShip.getYPosition() + spaceShipOnY + 0.2f, spaceShip.getZPosition() + spaceShipOnZ - 2,1.7f,0.6f,4 };
		ColBox *colShip2 = new ColBox{ spaceShip.getXPosition() + spaceShipOnX - 2.8f, spaceShip.getYPosition() + spaceShipOnY + 0.2f, spaceShip.getZPosition() + spaceShipOnZ + 0.5f,6.0f,0.6f,1 };
	
		Model = Save;
		// Geht die Gates durch
		for (int i = 0; i < 5; i++)
		{
			Gate *g(gateList.at(i));
			std::vector <ColBox*> l = g->getColBox();
			ColBox *b = l[0];
			// Collisionsdetection 
			// Erste Erkennung welches Gate in der Nähe ist und speichert die ID des Gates
			if (colDetection(*b, *colShip )) {
				collision = true;
				objID = i;
			}
			if (colDetection(*b, *colShip2)) {
				collision = true;
				objID = i;
			}
						
			// Zeichnet Gate
			g->draw(Model);
			Model = Save;			
			
		}
		

		// Wenn kein Gate in der Nähe = Schiff bewegen
		if (!collision) {
			spaceShip.setPosition((spaceShip.getXPosition() + spaceShipOnX), (spaceShip.getYPosition() + spaceShipOnY), (spaceShip.getZPosition() + spaceShipOnZ));	
			// Zeichnet Schiff
			spaceShip.draw(Model, programID);
			Model = Save;
			Model = glm::translate(Model, glm::vec3(-spaceShipOnX, -spaceShipOnY, -spaceShipOnZ));
		} else {
			bool collision = false;
			Gate *g(gateList.at(objID));
			std::vector <ColBox*> colBoxList = g->getColBox();	
			// Prüft die Kleineren Kollisionsboxen um das Gate.
			for (int i = 1; i < colBoxList.size(); i++) {				
				if (colDetection(*colBoxList[i], *colShip)) {
					collision = true;					
				}
				if (colDetection(*colBoxList[i], *colShip2)) {
					collision = true;
					
				}
			}
			// Wenn keine Kollision = Schiff bewegen
			if (!collision) {
				spaceShip.setPosition((spaceShip.getXPosition() + spaceShipOnX), (spaceShip.getYPosition() + spaceShipOnY), (spaceShip.getZPosition() + spaceShipOnZ));		
				// Zeichnet Schiff
				spaceShip.draw(Model,programID);
				Model = Save;
				Model = glm::translate(Model, glm::vec3(-spaceShipOnX, -spaceShipOnY, -spaceShipOnZ));
			}
			else {
				spaceShip.draw(Model, programID);
				Model = Save;

			}
		}	
		
		Model = glm::rotate(Model, angleX, glm::vec3(0, 1, 0));
		Model = glm::rotate(Model, angleY, glm::vec3(1, 0, 0));
		Model = glm::rotate(Model, angleZ, glm::vec3(0, 0, 1));
		//glm::vec3 l = glm::vec3(spaceShip.getXPosition(), spaceShip.getYPosition(), spaceShip.getZPosition()+300);
		glUniform3f(0, 0, 0, -3);		

		//glm::vec4 lpw = Model * glm::vec4(0, 0, 0.4, 1);

		// Lighting of world
		glm::vec4 lightPositionWorld = Model * glm::vec4(.0, 3.0, -30.0, 1.0);
		glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPositionWorld.x, lightPositionWorld.y, lightPositionWorld.z);
		
		glFlush();
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}

