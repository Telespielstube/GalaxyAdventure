#pragma once

/*	Enthält die X Y Z Koordinaten und den Winkel eines Objektes
	

	@autor	Vassilios Tsankis s0558527
*/
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
	
	

protected:
	float x;	// X Koordinate im Raum
	float y;	// Y Koordinate im Raum
	float z;	// Z Koordinate im Raum
	float xAngle;	// Wie das Objekt im Winkel X steht
	float yAngle;	// Wie das Objekt im Winkel Y steht
	float zAngle;	// Wie das Objekt im Winkel Z steht
};

