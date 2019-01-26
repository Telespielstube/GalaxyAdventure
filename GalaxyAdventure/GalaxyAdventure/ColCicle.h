#pragma once
#include "Col.h"
#include "ColBox.h"

class ColCicle : public Col
{
public:
	ColCicle();
	ColCicle(Position p, float radius, float cZ);
	~ColCicle();	
	float getRadius();
	float getColZ();
	ColCicle addPosition(Position p);

protected:
	float r, colZ;
};

