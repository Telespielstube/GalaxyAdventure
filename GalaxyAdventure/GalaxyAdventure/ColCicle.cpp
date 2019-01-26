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

float ColCicle::getRadius()
{
	return r;
}

float ColCicle::getColZ()
{
	return colZ;
}

ColCicle ColCicle::addPosition(Position p)
{
	return *new ColCicle(p.adPosition(position),r,colZ);
}
