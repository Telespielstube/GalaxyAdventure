#include "Position.h"



Position::Position(float posX, float posY, float posZ)
{
	x = posX;
	y = posY;
	z = posZ;
}

Position::Position()
{
	x = 0;
	y = 0;
	z = 0;
}

Position::~Position()
{
}

float Position::getX()
{
	return x;
}

float Position::getY()
{
	return y;
}

float Position::getZ()
{
	return z;
}

void Position::setPosition(float posX, float posY, float posZ)
{
	x = posX;
	y = posY;
	z = posZ;
}


