#include "ColBox.h"

/*
Klasse: ColBox

KollisonsBox in Form eines W�rfels.
x,y,z ist der erste Punkt des W�rfels
cX, cY, cZ ist die Gr��e des W�rfels

*/

// Constructor
ColBox::ColBox()
{

}

/** Collision box constructor
*
*	@param	p		position of collision box.
*	@param	cX		
*	@param	cY
*	@param	cZ
*
*/
ColBox::ColBox(Position p, float cX, float cY, float cZ)
{
	position.setPosition(p);
	colX = cX;
	colY = cY;
	colZ = cZ;
}

// Destructor
ColBox::~ColBox()
{
}

/** Returns the size of the box on the x axis.
*
*	@return		size of the box on x.
*
*/
float ColBox::getColX()
{
	return colX;
}

/** Returns the size of the box on the y axis.
*
*	@return		size of the box on y.
*
*/
float ColBox::getColY()
{
	return colY;
}

/** Returns the size of the box on the z axis.
*
*	@return		size of the box on z.
*
*/
float ColBox::getColZ()
{
	return colZ;
}

/** Returns the position of the new box.
*
*	@return		position of the new box.
*
*/
ColBox ColBox::addPosition(Position p)
{
	return *new ColBox(p.adPosition(position),colX,colY,colZ);
}


	

