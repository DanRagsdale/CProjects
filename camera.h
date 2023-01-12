#pragma once

#include "vec3.h"
#include "ray.h"

typedef struct camera 
{
	vec3 origin;
	vec3 horizontal;
	vec3 vertical;
	vec3 top_left;
} camera;


ray camera_get_ray(camera* cam, double dx, double dy)
{
	return ray_construct(cam->origin, vec3_add(3, cam->top_left, vec3_scaled(cam->horizontal, dx), vec3_scaled(cam->vertical, dy)));
}