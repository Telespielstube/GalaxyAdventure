#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RandomNumber.h"

RandomNumber::RandomNumber()
{
}

/** Initializes the random number generator
*/
void RandomNumber::initializeGenerator()
{
	srand(time(NULL));
}

/** Calcuates the random number.
*/
float RandomNumber::generateRandomNumber(float max, float min)
{
	float tempValue = ((float)rand()) / (float)RAND_MAX;
	return min + (tempValue * (max - min + .5f));
}

RandomNumber::~RandomNumber()
{
}
