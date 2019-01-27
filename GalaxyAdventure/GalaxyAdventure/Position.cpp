#include "Position.h"



Position::Position(float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
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

float Position::getAngleZ()
{
	return zAngle;
}

void Position::setAngleX(float angleX)
{
	xAngle = angleX;
}

void Position::setAngleY(float angleY)
{
	yAngle = angleY;
}

void Position::setAngleZ(float angleZ)
{
	zAngle = angleZ;
}


void Position::setPosition(float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = angleX;
	yAngle = angleY;
	zAngle = angleZ;
}

Position Position::adPosition(Position p1)
{
	return Position(p1.getX() + getX(), p1.getY() + getY(), p1.getZ() + getZ(),p1.getAngleX()+getAngleX(), p1.getAngleY() + getAngleY(), p1.getAngleZ() + getAngleZ());
}

void Position::setPosition(Position p)
{
	x = p.getX();
	y = p.getY();
	z = p.getZ();
	xAngle = p.getAngleX();
	yAngle = p.getAngleY();
	yAngle = p.getAngleZ();
}

void Position::setPosition(Position p, float angleX, float angleY, float angleZ)
{
	x = p.getX();
	y = p.getY();
	z = p.getZ();
	xAngle = p.getAngleX();
	yAngle = p.getAngleY();
	yAngle = p.getAngleZ();
}


