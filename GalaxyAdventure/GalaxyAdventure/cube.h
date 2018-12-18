#pragma once
class cube
{
public:
	cube(float, float, float, float, float, float);
	void drawCube(int);
	~cube();
	float getColX();
	float getColY();
	float getColZ();
	float getPosX();
	float getPosY();
	float getPosZ();
private:	
	float x, y, z, cX, cY, cZ;
};

