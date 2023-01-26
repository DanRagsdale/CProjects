#pragma once

#include <math.h>

#include "raytrace.h"
#include "vec3.h"
#include "ray.h"

typedef struct camera 
{
	vec3 origin;
	vec3 horizontal;
	vec3 vertical;
	vec3 top_left;
} camera;


camera camera_construct(vec3 origin, vec3 look_dir, double hfov)
{
	camera cam;
	cam.origin = origin;


	double half_width = tan(hfov * 0.5 * 3.14159 / 180);
	double width = 2 * half_width;
	double height = width / ASPECT_RATIO;


	cam.horizontal = vec3_scaled(vec3_normalized(vec3_cross(look_dir, vec3_construct(0,1,0))), width);
	cam.vertical = vec3_scaled(vec3_normalized(vec3_cross(cam.horizontal, look_dir)), -height);

	cam.top_left = vec3_add(4, origin, vec3_scaled(cam.horizontal, -0.5), vec3_scaled(cam.vertical, -0.5), vec3_normalized(look_dir));

	return cam;
}

camera camera_construct_lookpoint(vec3 origin, vec3 look_point, double hfov)
{
	vec3 look_dir = vec3_subtract(look_point, origin);
	return camera_construct(origin, look_dir, hfov);
}

ray camera_get_ray(camera* cam, double dx, double dy)
{
	return ray_construct(cam->origin, vec3_add(4, cam->top_left, vec3_negative(cam->origin), vec3_scaled(cam->horizontal, dx), vec3_scaled(cam->vertical, dy)));
}