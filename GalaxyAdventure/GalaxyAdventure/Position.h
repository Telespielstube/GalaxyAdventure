#pragma once
class Position
{
public:
	Position(float posX, float posY, float posZ, float angleX, float angleY);
	Position();
	~Position();
	float getX();
	float getY();
	float getZ();
	float getAngleX();
	float getAngleY();
	void setAngleX(float angleX);
	void setAngleY(float angleY);
	void setPosition(float posX, float posY, float posZ, float angleX, float angleY);
	

private:
	float x, y, z;
	float xAngle;
	float yAngle;
};

