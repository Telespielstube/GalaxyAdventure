#pragma once
#include "Position.h"
class ColBox
{

public:
	ColBox();	
	ColBox(float x, float y, float z, float cX, float cY, float cZ);
	virtual ~ColBox();
	float getColX();
	float getColY();
	float getColZ();
	float getPosX();
	float getPosY();
	float getPosZ();
	bool checkCollision(Position p, Position p1, ColBox b);

private:
	float colX, colY, colZ, posX, posY, posZ;





};