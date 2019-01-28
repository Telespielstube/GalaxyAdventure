#include "ColCicle.h"


// Constructor
ColCicle::ColCicle()
{
}

/** Constructor
*
*	@param	p			position of the collision circle.
*	@param	radius		radius of the circle
*	@param	cZ			z axis value of collision.
*
*/
ColCicle::ColCicle(Position p, float radius, float cZ)
{
	position = p;
	colZ = cZ;
	r = radius;
}

// Destructor
ColCicle::~ColCicle()
{
	position.setPosition(Position(0, 0, 0));
	r = 0;
}

/** Returns the radius of the circle.
*
*	@return		radius
*
*/
float ColCicle::getRadius()
{
	return r;
}

/** Get collision position on z axis.
*
*	@return		z position.
*
*/
float ColCicle::getColZ()
{
	return colZ;
}

/** Adds the new position for the collision circle.
*
*	@param	p		new position of the collision circle.
*
*	@return			new Circle on a new position.
*
*/
ColCicle ColCicle::addPosition(Position p)
{
	return *new ColCicle(p.adPosition(position),r,colZ);
}

/** Adds a scale to the circle.
*
*	@param	s	factor to scale the object.
*
*	@return		new scaled cirle.
*
*/
ColCicle ColCicle::addScaleF(float s)
{
	return *new ColCicle(Position(0,0,0), r*s, colZ*s);
}
