#pragma once
#include "Col.h"

/*	KollisionBox in Form eines Rechteckes

	@autor	Vassilios Tsankis s0558527
*/
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