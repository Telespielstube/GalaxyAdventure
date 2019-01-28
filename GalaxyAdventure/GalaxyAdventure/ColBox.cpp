#include "ColBox.h"


/* StandardKonstruktor
*/
ColBox::ColBox()
{

}

/*	Konstruktor

	@param	p	Die Position der Kollisionsbox
	@param	cX	Die Breite auf der X - Achse
	@param	cY	Die Breite auf der Y - Achse
	@param	cZ	Die Breite auf der Z - Achse
*/
ColBox::ColBox(Position p, float cX, float cY, float cZ)
{
	position.setPosition(p);
	colX = cX;
	colY = cY;
	colZ = cZ;
}

/*	Destruktor
*/
ColBox::~ColBox()
{
}

/* Gibt die Breite auf der X-Achse der KollisonsBox zurück

	@return	die Breite auf der X-Achse
*/
float ColBox::getColX()
{
	return colX;
}

/* Gibt die Breite auf der Y-Achse der KollisonsBox zurück

	@return	die Breite auf der Y-Achse
*/
float ColBox::getColY()
{
	return colY;
}

/* Gibt die Breite auf der Z-Achse der KollisonsBox zurück

	@return	die Breite auf der Z-Achse
*/
float ColBox::getColZ()
{
	return colZ;
}

/*	Addiert die Übergebene Posision auf die Akktuelle Position der KollisionsBox

	 @param	p	Position die dazuaddiert werden soll.
*/
ColBox ColBox::addPosition(Position p)
{
	return *new ColBox(p.adPosition(position),colX,colY,colZ);
}


	

