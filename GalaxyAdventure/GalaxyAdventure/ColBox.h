#pragma once
class ColBox
{
public:
	ColBox();
	// Consturktor
	ColBox(float x, float y, float z);
	virtual ~ColBox();
	float getColX();
	float getColY();
	float getColZ();


private:
	float colX, colY, colZ;


};