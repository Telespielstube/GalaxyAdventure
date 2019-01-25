#pragma once
class Position
{
public:
	Position(float posX, float posY, float posZ);
	Position();
	~Position();
	float getX();
	float getY();
	float getZ();
	void setPosition(float posX, float posY, float posZ);
	

private:
	float x, y, z;
};

