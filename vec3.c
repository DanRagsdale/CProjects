#include <stdio.h>
#include <stdarg.h>
#include <math.h>

#include "vec3.h"
#include "raytrace.h"

vec3 vec3_construct(double x, double y, double z)
{
	vec3 output;
	output.x = x;
	output.y = y;
	output.z = z;
	return output;
}

vec3 vec3_random_in_range(double min, double max)
{
	return vec3_construct(rand_range(min, max),rand_range(min, max),rand_range(min, max));
}

vec3 vec3_random_in_unit_sphere()
{
	while(1)
	{
		vec3 test_vec = vec3_random_in_range(-1,1);
		if(vec3_length_squared(test_vec) <= 1)
		{
			return test_vec;
		}
	}
}

vec3 vec3_random_unit()
{
	return vec3_normalized(vec3_random_in_unit_sphere());
}

double vec3_length(vec3 input)
{
	return sqrt(vec3_length_squared(input));
}

double vec3_length_squared(vec3 input)
{
	return vec3_dot(input, input);
}

double vec3_dot(vec3 A, vec3 B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

vec3 vec3_add(int count,...)
{
	va_list valist;
	double tot_x = 0, tot_y = 0, tot_z = 0;
	
	va_start(valist, count);
	for (int i=0; i < count; i++)
	{
		vec3 temp = va_arg(valist, vec3);
		tot_x += temp.x;
		tot_y += temp.y;
		tot_z += temp.z;
	}

	va_end(valist);
	return vec3_construct(tot_x, tot_y, tot_z);
}

vec3 vec3_subtract(vec3 A, vec3 B)
{
	return vec3_add(2, A, vec3_scaled(B, -1));
}

vec3 vec3_scaled(vec3 input, double t)
{
	return vec3_construct(input.x * t, input.y * t, input.z * t);
}

vec3 vec3_normalized(vec3 input)
{
	double norm = vec3_length(input);
	return vec3_scaled(input, 1 / norm);
}


void vec3_print_color(vec3 input)
{
	//Gamma correction
	double gr = sqrt(input.x);
	double gg = sqrt(input.y);
	double gb = sqrt(input.z);

	int ir = (int) (255 * gr);
	int ig = (int) (255 * gg);
	int ib = (int) (255 * gb);
	
	printf("%d %d %d\n", ir, ig, ib);
}