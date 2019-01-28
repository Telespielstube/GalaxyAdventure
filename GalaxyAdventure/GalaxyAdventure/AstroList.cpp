#include "AstroList.h"
#include "RandomNumber.h"


// Standard constructor
AstroList::AstroList()
{
	
}

/** Overloaded constructor.
*
*	@param	p		the position of the asteroid.
*	@param	d		the direction of the asteroid.
*	@param	s		the speed of the asteroid.
*	@param	size	the size of the asteroid.
*
*/
AstroList::AstroList(Position p, Position d, float s, float size)
{
	position = p;
	direction = d;
	speed = s;
	this->size = size;
}

// Destructor
AstroList::~AstroList()
{
}

/** Gets the asteroid position.
*
*	@return		position of the asteroid.
*
*/
Position AstroList::getPosition()
{
	return position;
}

/**SGets the asteroid position.
*
*	@param	p	position of the asteroid.
*
*/
void AstroList::setPosition(Position p)
{
	position = p;
}

/** Gets the asteroid direction.
*
*	@return		direction of the asteroid.
*
*/
Position AstroList::getDirection()
{
	return direction;
}

/** Gets the asteroid speed.
*
*	@return		speed of the asteroid.
*
*/
float AstroList::getSpeed()
{
	return speed;
}

/** Gets the asteroid size.
*
*	@return		sizeof the asteroid.
*
*/
float AstroList::getSize()
{
	return size;
}

/** Sets the asteroid size.
*
*	@param		size of the asteroid.
*
*/
void AstroList::setSize(float s)
{
	size = s;
}
