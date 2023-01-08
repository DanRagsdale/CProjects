#include "ray.h"
#include "vec3.h"

vec3 ray_at(ray* r, double t)
{
	double new_x = r->origin.x + t * r->direction.x;
	double new_y = r->origin.y + t * r->direction.y;
	double new_z = r->origin.z + t * r->direction.z;

	vec3 output = vec3_construct(new_x, new_y, new_z);

	return output;
}