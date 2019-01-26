#pragma once
#include <math.h>
#include "Position.h"

class Col
{
public:
	Col();
	~Col();
	Position getPosition();


protected:
	Position position;
};

