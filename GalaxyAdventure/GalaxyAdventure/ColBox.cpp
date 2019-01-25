#include "ColBox.h"


/*
Klasse: ColBox

KollisonsBox in Form eines Würfels.
x,y,z ist der erste Punkt des Würfels
cX, cY, cZ ist die Größe des Würfels

*/

ColBox::ColBox()
{

}

ColBox::ColBox(float x, float y, float z, float cX, float cY, float cZ)
{
	posX = x;
	posY = y;
	posZ = z;
	colX = cX;
	colY = cY;
	colZ = cZ;
}

ColBox::~ColBox()
{
}

float ColBox::getColX()
{
	return colX;
}

float ColBox::getColY()
{
	return colY;
}

float ColBox::getColZ()
{
	return colZ;
}

float ColBox::getPosX()
{
	return posX;
}

float ColBox::getPosY()
{
	return posY;
}

float ColBox::getPosZ()
{
	return posZ;
}

bool ColBox::checkCollision(Position p, Position p1, ColBox b)
{
	
	if (p.getX() + posX + colX >= p1.getX() + b.getPosX() && p1.getX() + b.getPosX() + b.getColX() >= p.getX() + posX &&
		p.getY() + posY + colY >= p1.getY() + b.getPosY() && p1.getY() + b.getPosY() + b.getColY() >= p.getY() + posY &&
		p.getZ() + posZ + colZ >= p1.getZ() + b.getPosZ() && p1.getZ() + b.getPosZ() + b.getColZ() >= p.getZ() +posZ) {
		return true;
	}
	else {
		return false;
	}
	
}
