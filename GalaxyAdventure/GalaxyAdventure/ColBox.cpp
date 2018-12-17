#include "ColBox.h"



float colX, colY, colZ;

ColBox::ColBox()
{

}

ColBox::ColBox(float x, float y, float z)
{
	colX = x;
	colY = y;
	colZ = z;
}

ColBox::~ColBox()
{
}

float ColBox::getColX()
{
	return colX;
}

float ColBox::getColY()
{
	return colY;
}

float ColBox::getColZ()
{
	return colZ;
}
