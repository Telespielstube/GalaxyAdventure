#pragma once
class ColBox
{

public:
	ColBox();
	// Consturktor
	ColBox(float x, float y, float z, float cX, float cY, float cZ);
	virtual ~ColBox();
	float getColX();
	float getColY();
	float getColZ();
	float getPosX();
	float getPosY();
	float getPosZ();

private:
	float colX, colY, colZ, posX, posY, posZ;





};