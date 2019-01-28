#include "Position.h"

/** Overloaded Constructor
*
*	@param	posX		x axis position
*	@param	PosY		y axis position
*	@param	posZ		z axis position
*	@param	angleX		x angle position
*	@param	angleY		y angle	position
*	@param	angleZ		z angle	position 
*/
Position::Position(float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = angleX;
	yAngle = angleY;

}

/** Overloaded Constructor
*
*	@param	posX		x axis position
*	@param	PosY		y axis position
*	@param	posZ		z axis position
*	
*/
Position::Position(float posX, float posY, float posZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = 0;
	yAngle = 0;
}

// Standard Constructor
Position::Position()
{
	x = 0;
	y = 0;
	z = 0;
	xAngle = 0;
	yAngle = 0;
}

// Destructor
Position::~Position()
{
}

/** Returns positon on x axis.
*
*	@return	x position.
*
*/
float Position::getX()
{
	return x;
}

/** Returns positon on y axis.
*
*	@return	y position.
*
*/
float Position::getY()
{
	return y;
}

/** Returns positon on z axis.
*
*	@return	z position.
*
*/
float Position::getZ()
{
	return z;
}

/** Return angle on x axis.
*
*	@return	x angle.
*
*/
float Position::getAngleX()
{
	return xAngle;
}

/** Return angle on y axis.
*
*	@return	y angle.
*
*/
float Position::getAngleY()
{
	return yAngle;
}

/** Return angle on z axis.
*
*	@return	z angle.
*
*/
float Position::getAngleZ()
{
	return zAngle;
}

/** Sets an angle on x axis.
*
*	@param angleX	float value for angle on x.
*
*/
void Position::setAngleX(float angleX)
{
	xAngle = angleX;
}

/** Sets an angle on x axis.
*
*	@param angleY	float value for angle on y.
*
*/
void Position::setAngleY(float angleY)
{
	yAngle = angleY;
}

/** Sets an angle on x axis.
*
*	@param angleZ	float value for angle on z.
*
*/
void Position::setAngleZ(float angleZ)
{
	zAngle = angleZ;
}

/** Sets a specific position for an object.
*
*	@param	posX		x axis position
*	@param	PosY		y axis position
*	@param	posZ		z axis position
*	@param	angleX		x angle position
*	@param	angleY		y angle	position
*	@param	angleZ		z angle	position
*
*/
void Position::setPosition(float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = angleX;
	yAngle = angleY;
	zAngle = angleZ;
}

/** Gets the position and angle of an object in the scene.
*
*	@param	p1	position of an object.
*
*	@return		the position and angle of an object.
*/
Position Position::adPosition(Position p1)
{
	return Position(p1.getX() + getX(), p1.getY() + getY(), p1.getZ() + getZ(),p1.getAngleX()+getAngleX(), p1.getAngleY() + getAngleY(), p1.getAngleZ() + getAngleZ());
}

/** Sets the position and angle of an object in the scene.
*
*	@param	p1	position of an object.
*
*/
void Position::setPosition(Position p)
{
	x = p.getX();
	y = p.getY();
	z = p.getZ();
	xAngle = p.getAngleX();
	yAngle = p.getAngleY();
	yAngle = p.getAngleZ();
}

/** Sets a specific position for an object.
*
*	@param	p			
*	@param	angleX		x angle position
*	@param	angleY		y angle	position
*	@param	angleZ		z angle	position
*
*/
void Position::setPosition(Position p, float angleX, float angleY, float angleZ)
{
	x = p.getX();
	y = p.getY();
	z = p.getZ();
	xAngle = p.getAngleX();
	yAngle = p.getAngleY();
	yAngle = p.getAngleZ();
}


