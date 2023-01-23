
#include <stdlib.h>
#include <math.h>

#include "raytrace.h"


double rand_unit()
{
	return rand() / (RAND_MAX + 1.0);
}

double rand_range(double min, double max) 
{
	return min + (max - min) * rand_unit();
}