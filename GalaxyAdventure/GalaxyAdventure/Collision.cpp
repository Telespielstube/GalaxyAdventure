#include "Collision.h"

/* Standard Konstruktor
*/
Collision::Collision()
{
}

/** Destruktor
*
*
*
*/
Collision::~Collision()
{
}

/* Überprüft die Kollision zwischen zwei Rechtecken

	@param	b1	Erste KollisionsBox
	@param	b2	Zweite KollisionsBox

	@return	gibt zurück ob eine Kollision vorliegt

*/
bool Collision::checkCollision(ColBox b1, ColBox b2) {
	if (b1.getPosition().getX() + b1.getColX() >= b2.getPosition().getX() && b2.getPosition().getX() + b2.getColX() >= b1.getPosition().getX() &&
		b1.getPosition().getY() + b1.getColY() >= b2.getPosition().getY() && b2.getPosition().getY() + b2.getColY() >= b1.getPosition().getY() &&
		b1.getPosition().getZ() + b1.getColZ() >= b2.getPosition().getZ() && b2.getPosition().getZ() + b2.getColZ() >= b1.getPosition().getZ()) {
		return true;
	}
	else {
		return false;
	}
}

/* Überprüft die Kollision zwischen einem Rechteck und einem Zylinder

	@param	b1	Kollisions Rechteck
	@param	c1	Kollsiions Zylinder

	@return	gibt zurück ob eine Kollision vorliegt

*/
bool Collision::checkCollision(ColBox b1, ColCicle c1)
{
	float x = b1.getPosition().getX();
	float y = b1.getPosition().getY();
	float z = b1.getPosition().getZ();

	// begrenzt den Z Bereich
	if (b1.getPosition().getZ() + b1.getColZ() >= c1.getPosition().getZ() && c1.getPosition().getZ() + c1.getColZ() >= b1.getPosition().getZ()) {

		//1. Prüfen ob der Kreismittelpunkt innerhalb des Rechteckes ist
		if (c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX() &&
			c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY() &&
			c1.getPosition().getZ() >= z && c1.getPosition().getZ() <= z + b1.getColZ())
			return true;

		//2. Prüfen ob die Ecken den Kreis berühren
		if (checkCollision(c1, ColCicle(Position(x, y, z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x, y, z + b1.getColZ()), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x, y + b1.getColY(), z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x, y + b1.getColY(), z + b1.getColZ()), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y, z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y, z + b1.getColZ()), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y + b1.getColY(), z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y + b1.getColY(), z + b1.getColZ()), 0, b1.getColZ())))
			return true;


		//3. Prüfen ob der Radius über die seiten geht.
		if (c1.getPosition().getX() + c1.getRadius() >= x && c1.getPosition().getX() <= x && c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY())
			return true;

		if (c1.getPosition().getX() - c1.getRadius() <= x + b1.getColX() && c1.getPosition().getX() >= x + b1.getColX() && c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY())
			return true;

		if (c1.getPosition().getY() + c1.getRadius() >= y && c1.getPosition().getY() <= y && c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX())
			return true;

		if (c1.getPosition().getY() - c1.getRadius() <= y + b1.getColY() && c1.getPosition().getY() >= y + b1.getColY() && c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX())
			return true;

	}


	return false;
}

/* Überprüft die Kollision zwischen einem Rechteck und einem Torus

	@param	b1	Kollisions Rechteck
	@param	c1	Kollsiions Zylinder
	@param	c2	schneidet einen Zylinder aus c1 raus, die keine Kollision verursachen soll.

	@return	gibt zurück ob eine Kollision vorliegt

*/
bool Collision::checkCollision(ColBox b1, ColCicle c1, ColCicle c2)
{
	bool col = checkCollision(b1, c1);
	if (col) {
		if (sqrt(pow(b1.getPosition().getX() - c2.getPosition().getX(), 2) + pow(b1.getPosition().getY() - c2.getPosition().getY(), 2)) <= c2.getRadius() &&
			sqrt(pow(b1.getPosition().getX() + b1.getColX() - c2.getPosition().getX(), 2) + pow(b1.getPosition().getY() - c2.getPosition().getY(), 2)) <= c2.getRadius() &&
			sqrt(pow(b1.getPosition().getX() + b1.getColX() - c2.getPosition().getX(), 2) + pow(b1.getPosition().getY() + b1.getColY() - c2.getPosition().getY(), 2)) <= c2.getRadius() &&
			sqrt(pow(b1.getPosition().getX() - c2.getPosition().getX(), 2) + pow(b1.getPosition().getY() + b1.getColY() - c2.getPosition().getY(), 2)) <= c2.getRadius())
			return false;
	}

	return col;
}

/* Überprüft die Kollision zwischen zwei Zylindern

	@param	c1	Erster Zylindern
	@param	c2	Zweiter Zylindern

	@return	gibt zurück ob eine Kollision vorliegt

*/
bool Collision::checkCollision(ColCicle c1, ColCicle c2)
{
	if (sqrt(pow(c2.getPosition().getX() - c1.getPosition().getX(), 2) + pow(c2.getPosition().getY() - c1.getPosition().getY(), 2)) <= c1.getRadius() + c2.getRadius() &&
		c1.getPosition().getZ() + c1.getColZ() >= c2.getPosition().getZ() && c2.getPosition().getZ() + c2.getColZ() >= c1.getPosition().getZ()) {
		return true;
	}
	else {
		return false;
	}
}


