#pragma once
#include <math.h>
#include "Position.h"

/*	KollisionBox
	enth�lt die verschiednen KolisionsBoxarten

	@autor	Vassilios Tsankis s0558527
*/
class Col
{
public:
	Col();
	~Col();
	Position getPosition();


protected:
	Position position;
};

