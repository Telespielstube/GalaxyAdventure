#include "ColCicle.h"



ColCicle::ColCicle()
{
}

ColCicle::ColCicle(Position p, float radius, float cZ)
{
	position = p;
	colZ = cZ;
	r = radius;
}


ColCicle::~ColCicle()
{
	position.setPosition(Position(0, 0, 0));
	r = 0;
}

bool ColCicle::checkColision(Position p, Position p1, ColCicle c){
	
	if ( sqrt( pow(p1.getX()-p.getX(),2) + pow(p1.getY()-p.getY(),2)) <= r + c.r && 
		p.getZ() + position.getZ() + colZ >= p1.getZ() + c.getPosition().getZ() && p1.getZ() + c.getPosition().getZ() + c.colZ >= p.getZ() + position.getZ()) {
		return true;
	}
	else {
		return false;
	}
	
}

bool ColCicle::checkColision(Position p, Position p1, ColBox b)
{
	float x = p1.getX() + b.getPosition().getX();
	float y = p1.getY() + b.getPosition().getY();
	float z = p1.getZ() + b.getPosition().getZ();

	bool col = false;
	if (p.getX() >= x && p.getX() <= x + b.getColX() &&
		p.getY() >= y && p.getY() <= y + b.getColY() &&
		p.getZ() >= z && p.getZ() <= z + b.getColZ()) 
		return true;
		
	
	if (checkColision(p, p1, ColCicle(Position(x, y, z), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x, y, z + b.getColZ()), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x, y + b.getColY(), z), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x, y + b.getColY(), z + b.getColZ()), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x + b.getColX(), y, z), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x + b.getColX(), y, z + b.getColZ()), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x + b.getColX(), y + b.getColY(), z), 0, b.getColZ())) ||
		checkColision(p, p1, ColCicle(Position(x + b.getColX(), y + b.getColY(), z + b.getColZ()), 0, b.getColZ())))
		return true;

	if (p.getZ() + position.getZ() + colZ >= p1.getZ() + b.getPosition().getZ() && p1.getZ() + b.getPosition().getZ() + b.getColZ() >= p.getZ() + position.getZ()) {
		if (p.getX() + r >= x && p.getX() <= x && p.getY() >= y && p.getY() <= y + b.getColY())
			return true;

		if (p.getX() - r <= x + b.getColX() && p.getX() >= x + b.getColX() && p.getY() >= y && p.getY() <= y + b.getColY())
			return true;

		if (p.getY() + r >= y && p.getY() <= y && p.getX() >= y && p.getX() <= x + b.getColX())
			return true;

		if (p.getY() - r <= y + b.getColY() && p.getY() >= y + b.getColY() && p.getX() >= x && p.getX() <= x + b.getColX())
			return true;
	}
	
		
	return false;
	
}

float ColCicle::getRadius()
{
	return r;
}
