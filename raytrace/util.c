
#include <stdlib.h>
#include <math.h>

#include "raytrace.h"

#define RAND_SIZE 10000
unsigned int counter;
double rand_unit()
{
	//return (counter % RAND_SIZE) / (double) RAND_SIZE; 
	return rand_r(&counter) / (RAND_MAX + 1.0);
}

double rand_range(double min, double max) 
{
	return min + (max - min) * rand_unit();
}