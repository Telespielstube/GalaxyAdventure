#pragma once
class Position
{
public:
	Position(float posX, float posY, float posZ, float angleX, float angleY);
	Position(float posX, float posY, float posZ);
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
	Position adPosition(Position p1);
	void setPosition(Position p);
	

protected:
	float x, y, z;
	float xAngle;
	float yAngle;
};

