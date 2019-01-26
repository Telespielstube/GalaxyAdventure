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

ColBox ColBox::addPosition(Position p)
{
	return *new ColBox(p.adPosition(position),colX,colY,colZ);
}


	

