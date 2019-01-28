#include "AstroList.h"
#include "RandomNumber.h"


/* Standard Konstruktor
*/
AstroList::AstroList()
{	
}

/*	Konstruktor

	@param	p	die Position des Astro
	@param	d	die Richtung des Astro
	@param	s	die Geschwindigkeit des Astro
	@param	size	die Faktorgr��e des Astro
*/
AstroList::AstroList(Position p, Position d, float s, float size)
{
	position = p;
	direction = d;
	speed = s;
	this->size = size;
}

/*	Destruktor
*/
AstroList::~AstroList()
{
}

/*	Gibt die Position des Astro zur�ck

	@return	Die Position
*/
Position AstroList::getPosition()
{
	return position;
}

/*	Setzt die Position des Astro
	
	@param	p	die Position
*/
void AstroList::setPosition(Position p)
{
	position = p;
}

/*	Gibt die Richtung des Astro zur�ck

	@return Die Richtung
*/
Position AstroList::getDirection()
{
	return direction;
}

/*	Gibt die Geschwindigkeit des Astro zur�ck

	@retrun die Geschwindigkeit
*/
float AstroList::getSpeed()
{
	return speed;
}

/*	gibt die Gr��e des Astro zur�ck

	@return die Gr��e
*/
float AstroList::getSize()
{
	return size;
}

/*	Setzt Faktorgr��e des Astro

	@param	s	die Faktor Gr��e
*/
void AstroList::setSize(float s)
{
	size = s;
}
