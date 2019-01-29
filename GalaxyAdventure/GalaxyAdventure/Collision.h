#pragma once
#include "ColBox.h"
#include "ColCicle.h"


/*	stellt Funktinen zur Kollisionserkennung bereit

	@autor	Vassilios Tsanakis s0558527
*/
class Collision
{
public:
	Collision();
	~Collision();
	bool checkCollision(ColBox b1, ColBox b2);
	bool checkCollision(ColBox b1, ColCicle c1);
	bool checkCollision(ColBox b1, ColCicle c1, ColCicle c2);
	bool checkCollision(ColCicle c1, ColCicle c2);
	
};

