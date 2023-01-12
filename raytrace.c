// Working through the raytracing in one weekend git book as a way to learn graphics and C
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"


const int OBJECT_COUNT = 2;
void* objects[2];
hit_test object_functions[2];

double rand_unit()
{
	return rand() / (RAND_MAX + 1.0);
}

double rand_range(double min, double max) 
{
	return min + (max - min) * rand_unit();
}

vec3 test_color(ray* r)
{
	hit_record hit;
	hit.t = -1.0;
	for(int i=0; i < 2; i++)
	{
		hit_record h = (*object_functions[i])(objects[i], r, 0, 10000);
		if(hit.t < 0)
		{
			hit = h;
		}
		if(h.t > 0 && h.t < hit.t)
		{
			hit = h;
		}
	}
	
	if(hit.t > 0)
	{
		return vec3_scaled(vec3_construct(hit.normal.x + 1, hit.normal.y + 1, hit.normal.z + 1), 0.5);
	}

	// Background
	vec3 unit_dir = vec3_normalized(r->direction);
	double fade = 0.5 * (1 + unit_dir.y);
	return vec3_construct(fade, fade, fade);
}

int main() 
{
	// Test Code
	//ray test_ray;
	//test_ray.origin = vec3_construct(0,0,0);
	//test_ray.direction = vec3_construct(1,1,0);
	//vec3 at = ray_at(&test_ray, 2);
	//fprintf(stderr, "%f, %f, %f", at.x, at.y, at.z);

	// Image Setup
	const int image_width = 400;
	const int image_height = 200;

	// World
	sphere s0 = sphere_construct(vec3_construct(0,0,-1), 0.5);
	sphere s1 = sphere_construct(vec3_construct(0,-100.5,-1), 100);
	objects[0] = &s0;
	objects[1] = &s1;
	object_functions[0] = &sphere_hit_test;
	object_functions[1] = &sphere_hit_test;

	// Camera Setup
	camera cam;

	double viewport_height = 2.0;
	double viewport_width = 4.0;
	double focal_length = 1.0;
	
	cam.origin = vec3_construct(0,0,0);
	cam.horizontal = vec3_construct(viewport_width, 0, 0);
	cam.vertical = vec3_construct(0, -viewport_height, 0);
	cam.top_left = vec3_construct(-viewport_width / 2, viewport_height / 2, -focal_length);

	// Render
	printf("P3\n%d %d\n255\n", image_width, image_height);

	int samples_per_pixel = 100;
	for(int j=0; j<image_height; j++)
	{
		fprintf(stderr, "Working on line %d of %d\n", j, image_height);
		for(int i=0; i<image_width; i++)
		{
			vec3 total_color = vec3_construct(0,0,0);
			for(int s=0; s<samples_per_pixel; s++)
			{
				double dx = (double) (i+rand_unit()) / (image_width - 1);
				double dy = (double) (j+rand_unit()) / (image_height - 1);

				ray r = camera_get_ray(&cam, dx, dy);
				total_color = vec3_add(2, total_color, test_color(&r));
			}
			vec3_print_color(vec3_scaled(total_color, 1.0 / samples_per_pixel));
		}
	}
}