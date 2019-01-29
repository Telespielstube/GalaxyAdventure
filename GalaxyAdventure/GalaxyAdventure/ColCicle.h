#pragma once
#include "Col.h"
#include "ColBox.h"

/*	KollisionBox in Form eines Zylinders
	Der Kreis befindet sich immer auf der Y-Achse und die Breite des Zylinders geht richtung Z-Achse

	@autor	Vassilios Tsankis s0558527
*/
class ColCicle : public Col
{
public:
	ColCicle();
	ColCicle(Position p, float radius, float cZ);
	~ColCicle();	
	float getRadius();
	float getColZ();
	ColCicle addPosition(Position p);
	ColCicle addScaleF(float s);

protected:
	float r, colZ;
};

