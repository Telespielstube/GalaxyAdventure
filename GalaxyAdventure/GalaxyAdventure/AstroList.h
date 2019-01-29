#pragma once
#include "Position.h"

/*	Enthält die Daten eines Asteroiden fuer eine Vektorliste ohne das Objekt selber haben zu müssen.

	@autor	Vassilios Tsankis s0558527
*/
class AstroList
{
public:
	AstroList();
	AstroList(Position p, Position d, float s, float size);
	~AstroList();
	Position getPosition();
	void setPosition(Position p);
	Position getDirection();
	float getSpeed();
	float getSize();
	void setSize(float s);

protected:
	Position position;
	Position direction;
	float speed;
	float size;
	Position rotation;


};

