#include <algorithm>  
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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
#include "Col.h"
#include "ColCicle.h"
#include "Collision.h"


GLuint programID;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
clock_t t1;


int main() {
	WindowInit windowInit;
	glewExperimental = true;
	Collision col;
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
	std::vector<Position*> gateList;
	int gateListSize = 5;

	gate = new Gate("../Object/Gate.obj", modelRenderer, gateTexture, gateTextureID);
	gate->setPosition(Position(0,0,0,0,0));	

	// Erstellt die Liste mit den Gates
	for (int i = 0; i < gateListSize; i++) {		
			gateList.push_back(new Position(rand() % 30 - 15, rand() % 30 - 15, -40 - (i * 40), 5, 90));			
	}	
		

	//////////////////////  Erstellung Sternenfeld  ///////////////////////////////////////
	std::vector<Position*> starField;
	std::vector<Position*> starField2;
	int numberOfStars = 80;
	star = new Star("../Object/Star.obj", modelRenderer, starTexture, starTextureID);
	star->setPosition(Position(0,0,0,0,0));
	for (int i = 0; i < numberOfStars; i++) {
		//Linke Feld
		starField.push_back(new Position(randomNumber.generateRandomNumber(-400.0f, -1500.0f), randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f),0,0));
		//Rechte Feld
		starField.push_back(new Position(randomNumber.generateRandomNumber(400.0f, 1500.0f), randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f), 0, 0));
		//Obere Feld
		starField.push_back(new Position(randomNumber.generateRandomNumber(-800.0f, 800.0f), randomNumber.generateRandomNumber(400.0f, 1500.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f), 0, 0));
		//Untere Feld
		starField.push_back(new Position(randomNumber.generateRandomNumber(-800.0f, 800.0f), randomNumber.generateRandomNumber(-400.0f, -1500.0f), randomNumber.generateRandomNumber(-500.0f, -1500.0f), 0, 0));
		// Hintere Feld
		if (i % 4 == 0) {
			starField2.push_back(new Position(randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-400.0f, 400.0f), randomNumber.generateRandomNumber(-1000.0f, -1500.0f), 0, 0));
		}			
	}

	//////////////////////////////
	

	// Setzt die Position des Schiffes
	spaceShip.setPosition(Position(0, 0, 0));
	
	
	int t1 = clock(); 
	float speed = .0f;	
	int t = 0;
	int z = 0;
	int aGate = 0; // Akktuelle GateID die durchflogen werden muss
	float grenzeZ = 40; // Spielfeldgrenze nach hinten
	bool moveShip = false;
	
	printf("Steuerung: W Hoch , S Runter, Pfeiltasten Richtung \n");
		
	
	//Game loop
	do {	
		moveShip = false;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.01f, 0.01f, 0.01f, 0.01f);
		
		//////// anpassung der Fenstergr��e wenn es ver�ndert wird //////////
		int width, height;
		int bottom = 0;
		int left = 0;
		glfwGetWindowSize(window, &width, &height);		
		// gleicht die Verzerrung aus.
		if ((width + 0.0) / (height + 0.0) > 2) {
			int owidth = width;
			width = (width / ((width + 0.0) / (height + 0.0))) * 2;
			left = (owidth - width) / 2;
		} else {
			int oheight = height;
			height = (height * ((width + 0.0) / (height + 0.0))) /2;
			bottom = (oheight - height) / 2;
		}
		glViewport(left,bottom, width, height);
		////////////////////////////////////////////////////////////////////


		// Geschwindigkeitsberechnung
		if (t == 100) {			
			speed = ((clock() - t1) / 350.0f);
			speed = 0.05f + (((speed) * 0.05f) - 0.05f);
			//std::cout << speed << std::endl;
			t1 = clock();
			
		}
		if (t < 101)
			t++;		
		
		
		float spaceShipOnX = controls.moveSpaceshipOnX(window, speed);
		float spaceShipOnY = controls.moveSpaceshipOnY(window, speed);
		float spaceShipOnZ = controls.moveSpaceshipOnZ(window, speed);
				

		// Zeichnen der Sterne an den Seiten. werden Verschoben sobald sie aus dem Blickfeld sind.		
		for (int i = 0; i < starField.size(); i++) {
			if (starField.at(i)->getZ() >= spaceShip.getPosition().getZ() - 300)
				starField.at(i)->setPosition(starField.at(i)->getX(), starField.at(i)->getY(), spaceShip.getPosition().getZ() - 1500, 0, 0);
			star->setPosition(*starField.at(i));
			star->draw(Model, programID);
		}
		// Zeichnen der Sterne hinten. Bewegen sich mit dem Schiff mit
		for (int i = 0; i < starField2.size(); i++) {
			star->setPosition(Position(starField2.at(i)->getX(), starField2.at(i)->getY(), spaceShip.getPosition().getZ() + starField2.at(i)->getZ()));
			star->draw(Model, programID);
		}

		glm::mat4 Save = Model;
		Model = glm::translate(Model, glm::vec3(1.5, 0, 0));	
		modelRenderer.sendMVP(Model);	
		Model = Save;

		bool collision = false;
		int objID = -1;		
		

		// Ausgabe Position des schiffes
		//std::cout << spaceShip.getPosition().getX() << " " << spaceShip.getPosition().getY() << " " << spaceShip.getPosition().getZ() << std::endl;

		// Geht die Gates durch
		for (int i = aGate; i < gateList.size(); i++)
		{
			gate->setPosition(*gateList[i]);			
			
			// Collisionsdetection 
			// Erste Erkennung welches Gate in der N�he ist und speichert die ID des Gates					
			if (col.checkCollision(spaceShip.getColBox()[0]->addPosition(spaceShip.getPosition()),gate->getColBox()[0]->addPosition(gate->getPosition()))) {
				collision = true;
				objID = i;				
			}		
			
			// Collisions Box zum pr�fen ob durchs Gate geflogen wurde.
			ColBox gt = *new ColBox(Position(-1.5f, -2.0f, -0.1f), 3, 4, 0.2f);
			ColBox st = *new ColBox(Position(0.0f, 0.0f, 2.5f, 0, 0), 0.0f, 0.0f, 0.5f);
			if (aGate == i)	
			if (col.checkCollision(gt.addPosition(gate->getPosition()), st.addPosition(spaceShip.getPosition()))) {
				std::cout << "Gate " << aGate << " durchflogen bei: " << spaceShip.getPosition().getX() << " " << spaceShip.getPosition().getY() << " " << spaceShip.getPosition().getZ() << std::endl;
				aGate++;					
				gateList.push_back(new Position(rand() % 30 - 15, rand() % 30 - 15, -40 - (i * 40) - 200,5,90));
				grenzeZ = spaceShip.getPosition().getZ() + 40;
				
			}			
			// Zeichnet Gate
			gate->draw(Model, programID);
			Model = Save;
		}		
		
		// Wenn kein Gate in der N�he = Schiff bewegen
		if (!collision) {
			//Spielbegrenzung
			if (spaceShip.getPosition().getX() + spaceShipOnX >= -60 && spaceShip.getPosition().getX() + spaceShipOnX <= 60 && spaceShip.getPosition().getY() + spaceShipOnY >= -60 && spaceShip.getPosition().getY() + spaceShipOnY <= 60 && spaceShip.getPosition().getZ() + spaceShipOnZ < grenzeZ) {				
				moveShip = true;							
			}
			else {
				moveShip = false;
				
			}
			
		} else {
			bool collision = false;
			gate->setPosition(*gateList.at(objID));			
			
			// Pr�ft die Kleineren Kollisionsboxen um das Gate.										
			for (int i = 1; i < gate->getColCicle().size(); i++) {
				for (int j = 1; j < spaceShip.getColBox().size(); j++) {					
					if (col.checkCollision(spaceShip.getColBox()[j]->addPosition(spaceShip.getPosition().adPosition(Position(spaceShipOnX,spaceShipOnY,spaceShipOnZ))),gate->getColCicle()[i]->addPosition(gate->getPosition()),*new ColCicle(gate->getPosition(),3.7, 0.68))) {
						collision = true;
					}
				}		
			}
			
			// Wenn keine Kollision = Schiff bewegen
			if (!collision) {
						
				moveShip = true;
				
			}
			else {
				moveShip = false;				
			}
		}				

		spaceShip.draw(Model, programID);
		Model = Save;
		if (moveShip) {
			spaceShip.setPosition(*new Position((spaceShip.getPosition().getX() + spaceShipOnX), (spaceShip.getPosition().getY() + spaceShipOnY), (spaceShip.getPosition().getZ() + spaceShipOnZ)));
			Model = glm::translate(Model, glm::vec3(-spaceShipOnX, -spaceShipOnY, -spaceShipOnZ));
		}
		
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

