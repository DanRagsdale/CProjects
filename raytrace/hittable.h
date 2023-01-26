#pragma once

#include "ray.h"

typedef struct hit_record hit_record;
typedef struct material material;

typedef hit_record (*hit_test)(void* object, ray* r, double t_min, double t_max);
//typedef int (*scatter)(ray* in_ray, hit_record* hr, vec3* attenuation, ray* scattered);

struct material
{
	vec3 color;
	double metalicity;
	double index_of_refraction;
	double transmissivity;
};

struct hit_record 
{
	double t;
	vec3 point;
	vec3 normal;
	material mat;
};