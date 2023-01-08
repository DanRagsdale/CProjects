#include <stdio.h>
#include <math.h>

#include "vec3.h"

vec3 vec3_construct(double x, double y, double z)
{
	vec3 output;
	output.x = x;
	output.y = y;
	output.z = z;
	return output;
}

double vec3_length(vec3 input)
{
	return sqrt(vec3_length_squared(input));
}

double vec3_length_squared(vec3 input)
{
	return input.x * input.x + input.y * input.y + input.z * input.z;
}

vec3 vec3_normalized(vec3 input)
{
	double norm = vec3_length(input);
	return vec3_construct(input.x / norm, input.y / norm, input.z / norm);
}

void vec3_print_color(vec3 input)
{
	int ir = (int) (255 * input.x);
	int ig = (int) (255 * input.y);
	int ib = (int) (255 * input.z);
	printf("%d %d %d\n", ir, ig, ib);
}