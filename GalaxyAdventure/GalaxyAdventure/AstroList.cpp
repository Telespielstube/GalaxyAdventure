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
	@param	size	die Faktorgröße des Astro
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

/*	Gibt die Position des Astro zurück

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

/*	Gibt die Richtung des Astro zurück

	@return Die Richtung
*/
Position AstroList::getDirection()
{
	return direction;
}

/*	Gibt die Geschwindigkeit des Astro zurück

	@retrun die Geschwindigkeit
*/
float AstroList::getSpeed()
{
	return speed;
}

/*	gibt die Größe des Astro zurück

	@return die Größe
*/
float AstroList::getSize()
{
	return size;
}

/*	Setzt Faktorgröße des Astro

	@param	s	die Faktor Größe
*/
void AstroList::setSize(float s)
{
	size = s;
}
