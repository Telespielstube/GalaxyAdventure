#include "Position.h"


/*	Konstruktor

	@param	posX	Position X im Raum
	@param	posY	Position Y im Raum
	@param	pasZ	Position Z im Raum
	@param	angleX	Winkel des Objektes auf der X Achse
	@param	angleY	Winkel des Objektes auf der Y Achse
	@param	angleZ	Winkel des Objektes auf der Z Achse
*/
Position::Position(float posX, float posY, float posZ, float angleX, float angleY, float angleZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = angleX;
	yAngle = angleY;
	zAngle = angleZ;
}

/* Konstruktor

	@param	posX	Position X im Raum
	@param	posY	Position Y im Raum
	@param	pasZ	Position Z im Raum
*/
Position::Position(float posX, float posY, float posZ)
{
	x = posX;
	y = posY;
	z = posZ;
	xAngle = 0;
	yAngle = 0;
	zAngle = 0;
}


/* Konstruktor
*/
Position::Position()
{
	x = 0;
	y = 0;
	z = 0;
	xAngle = 0;
	yAngle = 0;
	zAngle = 0;
}

/* Destruktor
*/
Position::~Position()
{
}

/*	Gibt die X Koordinate zurück

	@return
*/
float Position::getX()
{
	return x;
}

/*	Gibt die Y Koordinate zurück

	@return
*/
float Position::getY()
{
	return y;
}

/*	Gibt die Z Koordinate zurück

	@return
*/
float Position::getZ()
{
	return z;
}

/*	Gibt die X Achse des Objektes zurück

	@return
*/
float Position::getAngleX()
{
	return xAngle;
}

/*	Gibt die Y Achse des Objektes zurück

	@return
*/
float Position::getAngleY()
{
	return yAngle;
}

/*	Gibt die Z Achse des Objektes zurück

	@return
*/
float Position::getAngleZ()
{
	return zAngle;
}

/* Setzt den Winkel auf der X Achse

	@param	angleX	der Winkel
*/
void Position::setAngleX(float angleX)
{
	xAngle = angleX;
}

/* Setzt den Winkel auf der Y Achse

	@param	angleY	der Winkel
*/
void Position::setAngleY(float angleY)
{
	yAngle = angleY;
}

/* Setzt den Winkel auf der Z Achse

	@param	angleZ	der Winkel
*/

void Position::setAngleZ(float angleZ)
{
	zAngle = angleZ;
}


/*	Setzt die Position neu

	@param	posX	Position X im Raum
	@param	posY	Position Y im Raum
	@param	pasZ	Position Z im Raum
	@param	angleX	Winkel des Objektes auf der X Achse
	@param	angleY	Winkel des Objektes auf der Y Achse
	@param	angleZ	Winkel des Objektes auf der Z Achse
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

/*	Addiert der Position eine übergebenen Position hinzu und gibt diese zurück

	@param	p1	Die Position die Dazuaddiert werden soll.

	@retrun	Eine neue Position
*/
Position Position::adPosition(Position p1)
{
	return Position(p1.getX() + getX(), p1.getY() + getY(), p1.getZ() + getZ(),p1.getAngleX()+getAngleX(), p1.getAngleY() + getAngleY(), p1.getAngleZ() + getAngleZ());
}

/*	Setzt die Position neu

	@param	p1	Die neue Position
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




