#pragma once

#include "ray.h"

typedef struct hit_record 
{
	double t;
	vec3 point;
	vec3 normal;
} hit_record;

typedef hit_record (*hit_test)(void* object, ray* r, double t_min, double t_max);