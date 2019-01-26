#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::checkCollision(ColBox b1, ColBox b2)
{
	if (b1.getPosition().getX() + b1.getColX() >= b2.getPosition().getX() && b2.getPosition().getX() + b2.getColX() >= b1.getPosition().getX() &&
		b1.getPosition().getY() + b1.getColY() >= b2.getPosition().getY() && b2.getPosition().getY() + b2.getColY() >= b1.getPosition().getY() &&
		b1.getPosition().getZ() + b1.getColZ() >= b2.getPosition().getZ() && b2.getPosition().getZ() + b2.getColZ() >= b1.getPosition().getZ() ) {
		return true;
	}
	else {
		return false;
	}
}

bool Collision::checkCollision(ColBox b1, ColCicle c1)
{
	float x = b1.getPosition().getX();
	float y = b1.getPosition().getY();
	float z = b1.getPosition().getZ();

	bool col = false;
	if (b1.getPosition().getZ() + b1.getColZ() >= c1.getPosition().getZ() && c1.getPosition().getZ() + c1.getColZ() >= b1.getPosition().getZ()) {
	if (c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX() &&
		c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY() &&
		c1.getPosition().getZ() >= z && c1.getPosition().getZ() <= z + b1.getColZ())
		return true;


	if (checkCollision(c1, ColCicle(Position(x, y, z), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x, y, z + b1.getColZ()), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x, y + b1.getColY(), z), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x, y + b1.getColY(), z + b1.getColZ()), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x + b1.getColX(), y, z), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x + b1.getColX(), y, z + b1.getColZ()), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x + b1.getColX(), y + b1.getColY(), z), 0, b1.getColZ())) ||
		checkCollision(c1, ColCicle(Position(x + b1.getColX(), y + b1.getColY(), z + b1.getColZ()), 0, b1.getColZ())))
		return true;

	
		if (c1.getPosition().getX() + c1.getRadius() >= x && c1.getPosition().getX() <= x && c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY())
			return true;

		if (c1.getPosition().getX() - c1.getRadius() <= x + b1.getColX() && c1.getPosition().getX() >= x + b1.getColX() && c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY())
			return true;

		if (c1.getPosition().getY() + c1.getRadius() >= y && c1.getPosition().getY() <= y && c1.getPosition().getX() >= y && c1.getPosition().getX() <= x + b1.getColX())
			return true;

		if (c1.getPosition().getY() - c1.getRadius() <= y + b1.getColY() && c1.getPosition().getY() >= y + b1.getColY() && c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX())
			return true;
	}


	return false;
}

bool Collision::checkCollision(ColBox b1, ColCicle c1, ColCicle c2)
{
	float x = b1.getPosition().getX();
	float y = b1.getPosition().getY();
	float z = b1.getPosition().getZ();

	bool col = false;
	if (b1.getPosition().getZ() + b1.getColZ() >= c1.getPosition().getZ() && c1.getPosition().getZ() + c1.getColZ() >= b1.getPosition().getZ()) {
		if (c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX() &&
			c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY() &&
			c1.getPosition().getZ() >= z && c1.getPosition().getZ() <= z + b1.getColZ())
			col = true;


		if (!col &&
			checkCollision(c1, ColCicle(Position(x, y, z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x, y, z + b1.getColZ()), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x, y + b1.getColY(), z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x, y + b1.getColY(), z + b1.getColZ()), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y, z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y, z + b1.getColZ()), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y + b1.getColY(), z), 0, b1.getColZ())) ||
			checkCollision(c1, ColCicle(Position(x + b1.getColX(), y + b1.getColY(), z + b1.getColZ()), 0, b1.getColZ())))
			col = true;


		if (!col && c1.getPosition().getX() + c1.getRadius() >= x && c1.getPosition().getX() <= x && c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY())
			col = true;

		if (!col &&c1.getPosition().getX() - c1.getRadius() <= x + b1.getColX() && c1.getPosition().getX() >= x + b1.getColX() && c1.getPosition().getY() >= y && c1.getPosition().getY() <= y + b1.getColY())
			col = true;

		if (!col &&c1.getPosition().getY() + c1.getRadius() >= y && c1.getPosition().getY() <= y && c1.getPosition().getX() >= y && c1.getPosition().getX() <= x + b1.getColX())
			col = true;

		if (!col &&c1.getPosition().getY() - c1.getRadius() <= y + b1.getColY() && c1.getPosition().getY() >= y + b1.getColY() && c1.getPosition().getX() >= x && c1.getPosition().getX() <= x + b1.getColX())
			col = true;
	}

	if (col) {
		if (sqrt(pow(b1.getPosition().getX(), 2) + pow(b1.getPosition().getY(), 2)) <= sqrt(pow(c2.getPosition().getX(), 2) + pow(c2.getPosition().getY(), 2)) &&
			sqrt(pow(b1.getPosition().getX(), 2) + pow(b1.getPosition().getY()+b1.getColY(), 2)) <= sqrt(pow(c2.getPosition().getX(), 2) + pow(c2.getPosition().getY(), 2)) &&
			sqrt(pow(b1.getPosition().getX() + b1.getColX(), 2) + pow(b1.getPosition().getY(), 2)) <= sqrt(pow(c2.getPosition().getX(), 2) + pow(c2.getPosition().getY(), 2)) &&
			sqrt(pow(b1.getPosition().getX() + b1.getColX(), 2) + pow(b1.getPosition().getY()+ b1.getColY(), 2)) <= sqrt(pow(c2.getPosition().getX(), 2) + pow(c2.getPosition().getY(), 2)))
			return false;
	}

	return col;
}

bool Collision::checkCollision(ColCicle c1, ColCicle c2)
{
	if ( sqrt( pow(c2.getPosition().getX()-c1.getPosition().getX(),2) + pow(c2.getPosition().getY()-c1.getPosition().getY(),2)) <= c1.getRadius() + c2.getRadius() && 
		c1.getPosition().getZ() + c1.getColZ() >= c2.getPosition().getZ() && c2.getPosition().getZ() + c2.getColZ() >= c1.getPosition().getZ()) {
		return true;
	}
	else {
		return false;
	}
}


