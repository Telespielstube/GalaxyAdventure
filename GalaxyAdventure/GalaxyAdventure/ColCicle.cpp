#include "ColCicle.h"


/*	Standard Konstruktor
*/
ColCicle::ColCicle()
{
}

/*	Konstruktor

	@param	p	Die Position des Kollisions Zylinders
	@param	radis	Der Radius des Kreises vom Zylinder Y-Achse
	@param	cZ	Die Breite des Zylinders Z-Achse
*/
ColCicle::ColCicle(Position p, float radius, float cZ)
{
	position = p;
	colZ = cZ;
	r = radius;
}

/*	Destruktor
*/
ColCicle::~ColCicle()
{
	position.setPosition(Position(0, 0, 0));
	r = 0;
}

/*	Gibt den Radius zurück

	@return den Radius
*/
float ColCicle::getRadius()
{
	return r;
}

/*	Gibt die Breite des Zylinders zurück

	@return	die Breite
*/
float ColCicle::getColZ()
{
	return colZ;
}

/*	Addiert eine Weitere Position zur eigenen hinzu und gibt eine neue KollisionsBox zurück

	@param	p	Position die dazuadiert werden soll

	@return eine Neue KollisionsBox in form eines Zylinders
*/
ColCicle ColCicle::addPosition(Position p)
{
	return *new ColCicle(p.adPosition(position),r,colZ);
}

/*	Multipliziert die Größe mit einem Übergebenen Faktor
	
	@param	s	Der Faktor
	
	@return	eine neue Kollisionsbox in form eines Zylinders
*/
ColCicle ColCicle::addScaleF(float s)
{
	return *new ColCicle(Position(0,0,0), r*s, colZ*s);
}
