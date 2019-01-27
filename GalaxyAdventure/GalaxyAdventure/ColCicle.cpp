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

ColCicle ColCicle::addScaleF(float s)
{
	return *new ColCicle(Position(0,0,0), r*s, colZ*s);
}
