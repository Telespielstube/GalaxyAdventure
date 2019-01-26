#pragma once
#include "Col.h"
class ColBox : public Col
{

public:
	ColBox();	
	ColBox(Position p, float cX, float cY, float cZ);
	virtual ~ColBox();
	float getColX();
	float getColY();
	float getColZ();	
	
	ColBox addPosition(Position p);
private:
	float colX, colY, colZ;
};