#include "random.h"

long random(long min, long max)
{
	return min + ((((max-min))*rand())/(RAND_MAX+1));
}

int random(int min, int max)
{
	return min + ((((max-min))*rand())/(RAND_MAX+1));
}

float random(float min, float max)
{
	float tmp = (float)min + (float)(((float)((max-min))*rand())/(float)(RAND_MAX+1));
	return tmp;
}
