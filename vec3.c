#include <stdio.h>
#include <math.h>

#include "vec3.h"

double vec3_length(vec3 input)
{
	return sqrt(vec3_length_squared(input));
}

double vec3_length_squared(vec3 input)
{
	return input.x * input.x + input.y * input.y + input.z * input.z;
}

void vec3_print_color(vec3 input)
{
	int ir = (int) (255 * input.x);
	int ig = (int) (255 * input.y);
	int ib = (int) (255 * input.z);
	printf("%d %d %d\n", ir, ig, ib);
}