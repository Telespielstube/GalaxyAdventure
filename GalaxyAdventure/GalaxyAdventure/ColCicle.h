#pragma once
#include "Col.h"
#include "ColBox.h"

class ColCicle : public Col
{
public:
	ColCicle();
	ColCicle(Position p, float radius, float cZ);
	~ColCicle();
	bool checkColision(Position p, Position p1, ColCicle c);
	bool checkColision(Position p, Position p1, ColBox b);
	float getRadius();

protected:
	float r, colZ;
};

