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

ColBox::ColBox(Position p, float cX, float cY, float cZ)
{
	position.setPosition(p);
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


bool ColBox::checkCollision(Position p, Position p1, ColBox b)
{

	if (p.getX() + position.getX() + colX >= p1.getX() + b.getPosition().getX() && p1.getX() + b.getPosition().getX() + b.getColX() >= p.getX() + position.getX() &&
		p.getY() + position.getY() + colY >= p1.getY() + b.getPosition().getY() && p1.getY() + b.getPosition().getY() + b.getColY() >= p.getY() + position.getY() &&
		p.getZ() + position.getZ() + colZ >= p1.getZ() + b.getPosition().getZ() && p1.getZ() + b.getPosition().getZ() + b.getColZ() >= p.getZ() + position.getZ()) {
		return true;
	}
	else {
		return false;
	}
}


	

