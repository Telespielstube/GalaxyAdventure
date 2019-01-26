#include "Position.h"



Position::Position(float posX, float posY, float posZ, float angleX, float angleY)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = angleX;
	yAngle = angleY;

}

Position::Position(float posX, float posY, float posZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = 0;
	yAngle = 0;
}

Position::Position()
{
	x = 0;
	y = 0;
	z = 0;
	xAngle = 0;
	yAngle = 0;
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

float Position::getAngleX()
{
	return xAngle;
}

float Position::getAngleY()
{
	return yAngle;
}

void Position::setAngleX(float angleX)
{
	xAngle = angleX;
}

void Position::setAngleY(float angleY)
{
	yAngle = angleY;
}

void Position::setPosition(float posX, float posY, float posZ, float angleX, float angleY)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = angleX;
	yAngle = angleY;
}

void Position::setPosition(Position p)
{
	x = p.getX();
	y = p.getY();
	z = p.getZ();
	xAngle = p.getAngleX();
	yAngle = p.getAngleY();
}


