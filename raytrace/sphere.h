#pragma once

#include <math.h>

#include "raytrace.h"
#include "vec3.h"
#include "hittable.h"

typedef struct sphere
{
	vec3 center;
	double radius;
	material mat;
} sphere;

sphere sphere_construct(vec3 c, double r, material mat)
{
	sphere s;
	s.center = c;
	s.radius = r;
	s.mat = mat;
	return s;
}


hit_record sphere_hit_test(void* object, ray* r, double t_min, double t_max)
{
	hit_record h;
	
	sphere s = * (sphere*) object;

	vec3 test_orig = vec3_subtract(r->origin, s.center);
	double a = vec3_length_squared(r->direction);
	double b = 2 * vec3_dot(r->direction, test_orig);
	double c = vec3_length_squared(test_orig) - s.radius * s.radius;

	double discriminant = b*b - 4*a*c;
	if(discriminant < 0)
	{
		h.t = MAX_DIST;
	} else {
		h.t = (-b - sqrt(discriminant)) / (2*a);

		h.point = ray_at(r, h.t);
		h.normal = vec3_normalized(vec3_subtract(h.point, s.center));

		h.mat = s.mat;
	}

	return h;
}