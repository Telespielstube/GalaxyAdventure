#include "AstroList.h"
#include "RandomNumber.h"



AstroList::AstroList()
{
	
}

AstroList::AstroList(Position p, Position d, float s, float size)
{
	position = p;
	direction = d;
	speed = s;
	this->size = size;
}


AstroList::~AstroList()
{
}

Position AstroList::getPosition()
{
	return position;
}

void AstroList::setPosition(Position p)
{
	position = p;
}

Position AstroList::getDirection()
{
	return direction;
}

float AstroList::getSpeed()
{
	return speed;
}

float AstroList::getSize()
{
	return size;
}

void AstroList::setSize(float s)
{
	size = s;
}
