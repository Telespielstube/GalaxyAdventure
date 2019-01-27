#pragma once
class Position
{
public:
	Position(float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
	Position(float posX, float posY, float posZ);
	Position();
	~Position();
	float getX();
	float getY();
	float getZ();
	float getAngleX();
	float getAngleY();
	float getAngleZ();
	void setAngleX(float angleX);
	void setAngleY(float angleY);
	void setAngleZ(float angleZ);
	void setPosition(float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
	Position adPosition(Position p1);
	void setPosition(Position p);
	void setPosition(Position p, float angleX, float angleY, float angleZ);
	

protected:
	float x, y, z;
	float xAngle;
	float yAngle;
	float zAngle;
};

