#include <algorithm>  
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
#include "Windows.h"
#include "Star.h"

GLuint programID;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
float angleX;
float angleY;
float angleZ;
clock_t t1;

/** Kollisionsdetection
*
*	Pr�ft zwei �bergebene Kollisionsboxen ob sie sich ber�hren wenn ja wird true zur�ckgegben.
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
	
	// Loads shaders and textures.
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint shipTexture = loadBMP("../Texture/shipTexture.bmp");
	GLuint shipTextureID = glGetUniformLocation(programID, "shipObjTexture");
	GLuint gateTexture = loadBMP("../Texture/gateTexture.bmp");
	GLuint gateTextureID = glGetUniformLocation(programID, "gateObjTexture");
	GLuint starTexture = loadBMP("../Texture/starTexture.bmp");
	GLuint starTextureID = glGetUniformLocation(programID, "starObjTexture");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	glUseProgram(programID);
	glMatrixMode(GL_MODELVIEW);

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	Projection = glm::perspective(80.0f, 4.0f / 3.0f, 0.1f, 1500.0f);
	// Camera position
	glm::vec3 cameraPos = glm::vec3(0, 7, 12);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1);
	glm::vec3 cameraUp = glm::vec3(0.0f, 3.0f, 0.0f);
	View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::vec4 lightPositionWorld = Model * glm::vec4(.0f, 30.0f, 100.0f, 1.0f);
 
	Renderer modelRenderer(programID, Projection, View);
	Spaceship spaceShip("../Object/Ship.obj", modelRenderer, shipTexture, shipTextureID);
	Gate *gate;
	Star *star;
	RandomNumber randomNumber;
	randomNumber.initializeGenerator();
	Controls controls;
	std::vector<Gate*> gateList;
	int gateListSize = 5;

	for (int i = 0; i < gateListSize; i++)
	{
		
		gate = new Gate("../Object/Gate.obj", modelRenderer, gateTexture, gateTextureID);		
		gateList.push_back(gate);
		// Random Gate Position			
		gate->setPosition(rand() % 30 - 15, rand() % 30 - 15, -40 - (i * 40));

		gate->setXAngle(-5.0f);
		gate->setYAngle(90.0f);

		// Erzeugt die KollisionsBox um das Gate
		// Erste KollisionsBox ist �ber das Ganze Gate
		float s = 1.08;		
		
		float x = 4.22;
		float y =  0.5;
		float z =  0.68;

		float xCol = 0.58;
		float yCol = 1;
		float zCol = 1.36;


		//  ******************** Erstellung Kollisionsbox ums gate   *********************************

			// Erste Kollisionsbox Main box dient zur erkennung das Schiff in der n�he ist zum Gate
			gate->addColBox(new ColBox(gate->getXPosition() - 5, gate->getYPosition() - 5, gate->getZPosition() - 3.2, 10, 10, 4));

			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 4.2; y = 0.5; xCol = 0.6; yCol = 0.5;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 4.1; y = 1;	xCol = 0.6;	yCol = 0.25;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));
		
			x = 4.0; y = 1.25;	xCol = 0.65;	yCol = 0.25;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.9; y = 1.5;	xCol = 0.65;	yCol = 0.25;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.8; y = 1.75;	xCol = 0.7;	yCol = 0.25;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.7; y = 2;	xCol = 0.7;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.65; y = 2.125; xCol = 0.75;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.55; y = 2.25; xCol = 0.75;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.5; y = 2.375; xCol = 0.75;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.4; y = 2.5; xCol = 0.8;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.3; y = 2.625; xCol = 0.8;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.2; y = 2.75; xCol = 0.8;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.1; y = 2.875; xCol = 0.85;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 3.0; y = 3.0; xCol = 0.9;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 2.8; y = 3.125; xCol = 1.0;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 2.65; y = 3.25; xCol = 1.1;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 2.5; y = 3.375; xCol = 1.1;	yCol = 0.125;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 0.5; y = 3.6; xCol = 1;	yCol = 0.58;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 1; y = 3.5; xCol = 0.5;	yCol = 0.58;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));

			x = 1.5; y = 3.4; xCol = 0.5;	yCol = 0.58;
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() - x, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() + y, gate->getZPosition() - z, xCol, yCol, zCol));
			gate->addColBox(new ColBox(gate->getXPosition() + x - xCol, gate->getYPosition() - y - yCol, gate->getZPosition() - z, xCol, yCol, zCol));		

		//////////////////////////////////////////////
		
	}
		

	//////////////////////  Erstellung Sternenfeld  ///////////////////////////////////////
	std::vector<Star*> starField;
	int numberOfStars = 500;
	for (int i = 0; i < numberOfStars; i++)
	{
		star = new Star("../Object/Star.obj", modelRenderer, starTexture, starTextureID);
		star->setPosition(randomNumber.generateRandomNumber(-400.0f, -1500.0f), randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f));
		starField.push_back(star);

		star = new Star("../Object/Star.obj", modelRenderer, starTexture, starTextureID);
		star->setPosition(randomNumber.generateRandomNumber(400.0f, 1500.0f), randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f));
		starField.push_back(star);

		star = new Star("../Object/Star.obj", modelRenderer, starTexture, starTextureID);
		star->setPosition(randomNumber.generateRandomNumber( -800.0f, 800.0f), randomNumber.generateRandomNumber( 400.0f, 1500.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f));
		starField.push_back(star);

		star = new Star("../Object/Star.obj", modelRenderer, starTexture, starTextureID);
		star->setPosition(randomNumber.generateRandomNumber(-800.0f, 800.0f), randomNumber.generateRandomNumber(-400.0f, -1500.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f));
		starField.push_back(star);
		if (i % 4 == 0) {
			star = new Star("../Object/Star.obj", modelRenderer, starTexture, starTextureID);
			star->setPosition(randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-1000.0f, -1500.0f));
			starField.push_back(star);
		}
	}

	//////////////////////////////
	

	// Setzt die Position des Schiffes
	spaceShip.setPosition(.0f, .0f, .0f);
	
	
	int t1 = clock(); 
	float speed = .0f;
	int t = 0;
	int aGate = 0; // Akktuelle GateID die durchflogen werden muss
	
	
	//Game loop
	do
	{	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.01f, 0.01f, 0.01f, 0.01f);
		
		for (int i = 0; i < numberOfStars; i++)
			starField.at(i)->draw(Model, programID);
		
		// Geschwindigkeitsberechnung
		if (t == 200) {			
			speed = ((clock() - t1) / 700.0f);			
			speed = 0.05f + (((speed) * 0.05f) - 0.05f);
			t1 = clock();			
		}
		if (t < 201)
			t++;

		float spaceShipOnX = controls.moveSpaceshipOnX(window, speed);
		float spaceShipOnY = controls.moveSpaceshipOnY(window, speed);
		float spaceShipOnZ = controls.moveSpaceshipOnZ(window, speed);
		float angleX = controls.CamOnX(window, speed);
		float angleY = controls.CamOnY(window, speed);

				
		glm::mat4 Save = Model;
		Model = glm::translate(Model, glm::vec3(1.5, 0, 0));
	
		modelRenderer.sendMVP(Model);	
		
		bool collision = false;
		int objID = -1;

		// Kollisionsboxen f�r das Schiff. 
		// TODO. vll auch eine Main Kollisionsbox erstellen �ber das ganze Schiff.
		ColBox *colShip = new ColBox{ spaceShip.getXPosition() + spaceShipOnX - 3.1f, spaceShip.getYPosition() + spaceShipOnY - 0.45f, spaceShip.getZPosition() + spaceShipOnZ - 2.3f, 6.2f, 1.4f, 6.2f };
		ColBox *colShip2 = new ColBox{ spaceShip.getXPosition() + spaceShipOnX - 1.15f, spaceShip.getYPosition() + spaceShipOnY - 0.45f, spaceShip.getZPosition() + spaceShipOnZ - 2.3f, 2.3f, 1.4f, 6.2f };
		ColBox *colShip3 = new ColBox{ spaceShip.getXPosition() + spaceShipOnX -2.3f, spaceShip.getYPosition() + spaceShipOnY + 0.01f, spaceShip.getZPosition() + spaceShipOnZ + 1, 4.6f, 0.9f, 1.49f };
		ColBox *colShip4 = new ColBox{ spaceShip.getXPosition() + spaceShipOnX - 3.1f, spaceShip.getYPosition() + spaceShipOnY + 0.01f, spaceShip.getZPosition() + spaceShipOnZ + 1, 6.2, 0.4f, 1.49f };

		Model = Save;

		// Ausgabe Position des schiffes
		//std::cout << spaceShip.getXPosition() << " " << spaceShip.getYPosition() << " " << spaceShip.getZPosition() << std::endl;

		// Geht die Gates durch
		for (int i = 0; i < gateListSize; i++)
		{
			Gate *g(gateList.at(i));
			std::vector <ColBox*> l = g->getColBox();
			ColBox *b = l[0];
			// Collisionsdetection 
			// Erste Erkennung welches Gate in der N�he ist und speichert die ID des Gates
			if (colDetection(*b, *colShip)) {
				collision = true;
				objID = i;
			}			
			if (aGate == i)
				if (colDetection(*new ColBox{ g->getXPosition() - 1.5f,g->getYPosition() - 2.0f,g->getZPosition() - 0.1f,3,3,0.2 }, *new ColBox{ spaceShip.getXPosition(), spaceShip.getYPosition(), spaceShip.getZPosition() + 2.5f,0,0,0 })) {
					std::cout << "Gate " << aGate << " durchflogen bei: " << spaceShip.getXPosition() << " " << spaceShip.getYPosition() << " " << spaceShip.getZPosition() << std::endl;
					aGate++;
				}
			if (spaceShip.getZPosition() < gateList.at(i)->getZPosition())
			{				
				std::cout << gateList.size() << std::endl;
				gateList.push_back((gateList.at(i)));
				gateListSize++;
				g->setPosition(rand() % 30 - 15, rand() % 30 - 15, -40 - (i * 40) - 200);
			}
			// Zeichnet Gate
			g->draw(Model, programID);
			Model = Save;
		}

		
		
		
		// Wenn kein Gate in der N�he = Schiff bewegen
		if (!collision) {
			//Spielbegrenzung
			if (spaceShip.getXPosition() + spaceShipOnX >= -60 && spaceShip.getXPosition() + spaceShipOnX <= 60 && spaceShip.getYPosition() + spaceShipOnY >= -60 && spaceShip.getYPosition() + spaceShipOnY <= 60) {
				spaceShip.setPosition((spaceShip.getXPosition() + spaceShipOnX), (spaceShip.getYPosition() + spaceShipOnY), (spaceShip.getZPosition() + spaceShipOnZ));
				// Zeichnet Schiff
				spaceShip.draw(Model, programID);
				Model = Save;
				Model = glm::translate(Model, glm::vec3(-spaceShipOnX, -spaceShipOnY, -spaceShipOnZ));
			}
			else {
				spaceShip.draw(Model, programID);
				Model = Save;
			}
		} else {
			bool collision = false;
			Gate *g(gateList.at(objID));
			std::vector <ColBox*> colBoxList = g->getColBox();	
			// Pr�ft die Kleineren Kollisionsboxen um das Gate.			
			for (int i = 1; i < colBoxList.size(); i++) {								
				if (colDetection(*colBoxList[i], *colShip2)) {
					collision = true;					
				}
				if (colDetection(*colBoxList[i], *colShip3)) {
					collision = true;
				}	
				if (colDetection(*colBoxList[i], *colShip4)) {
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
		//glUniform3f(0, 0, 0, -3);		

		//glm::vec4 lpw = Model * glm::vec4(0, 0, 0.4, 1);
		
		// Lighting scene
		glUniform3f(glGetUniformLocation(programID, "LightPositionWorld"), lightPositionWorld.x, lightPositionWorld.y, lightPositionWorld.z);
		lightPositionWorld.z += controls.moveSpaceshipOnZ(window, speed);
		
		glFlush();
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	// Delete the text's VBO, the shader and the texture
	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}

