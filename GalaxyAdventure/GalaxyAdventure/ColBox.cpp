#include "ColBox.h"


/*
Klasse: ColBox

KollisonsBox in Form eines W�rfels.
x,y,z ist der erste Punkt des W�rfels
cX, cY, cZ ist die Gr��e des W�rfels

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