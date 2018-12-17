#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RandomNumberGenerator.h"


RandomNumberGenerator::RandomNumberGenerator()
{
}

float RandomNumberGenerator::randomNumber()
{
	/*float min = -10.0f;
	float max = 10.0f;
	float randomNumber = (float)rand() / RAND_MAX;

	return min + randomNumber * (max - min) + 1;*/
	return ((float)(rand()) / (float)(RAND_MAX) + 1.0f);
}

RandomNumberGenerator::~RandomNumberGenerator()
{
}
