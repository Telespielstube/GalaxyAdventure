#pragma once
class RandomNumber
{
public:
	RandomNumber();

	void initializeGenerator();
	float generateRandomNumber(float max, float min);
	~RandomNumber();
};

