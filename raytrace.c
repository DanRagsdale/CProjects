// Working through the raytracing in one weekend git book as a way to learn graphics and C
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "raytrace.h"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

const int MAX_DIST = 10000;

int MAX_COUNT = 1024;
int object_count = 0;
void* objects[1024];
hit_test object_functions[1024];

int scatter(ray* in_ray, hit_record* hr, vec3* attenuation, ray* scattered);
vec3 test_color(ray* r, int depth);

void add_object(void* obj, hit_test ht)
{
	objects[object_count] = obj;
	object_functions[object_count] = ht;

	object_count++;
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
	vec3 red = vec3_construct(1,0,0);
	material sphere_mat0;
	sphere_mat0.color = red;
	sphere_mat0.metalicity = 0.0;
	
	vec3 green = vec3_construct(0.8,0.8,0.8);
	material sphere_mat1;
	sphere_mat1.color = green;
	sphere_mat1.metalicity = 1.0; 
	
	vec3 blue = vec3_construct(0.3,0.3,0.9);
	material sphere_mat2;
	sphere_mat2.color = blue;
	sphere_mat2.metalicity = 0.9;

	sphere s0 = sphere_construct(vec3_construct(0,0,-1), 0.5, sphere_mat0);
	sphere s1 = sphere_construct(vec3_construct(0,-100.5,-1), 100, sphere_mat1);
	sphere s2 = sphere_construct(vec3_construct(2,0,-2), 1, sphere_mat2);
	sphere s3 = sphere_construct(vec3_construct(-2,0,-3), 0.5, sphere_mat0);


	add_object(&s0, &sphere_hit_test);
	add_object(&s1, &sphere_hit_test);
	add_object(&s2, &sphere_hit_test);
	add_object(&s3, &sphere_hit_test);

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

	const int SAMPLES_PER_PIXEL = 200;
	const int MAX_DEPTH = 50;
	for(int j=0; j<image_height; j++)
	{
		fprintf(stderr, "Working on line %d of %d\n", j, image_height);
		for(int i=0; i<image_width; i++)
		{
			vec3 total_color = vec3_construct(0,0,0);
			for(int s=0; s<SAMPLES_PER_PIXEL; s++)
			{
				double dx = (double) (i+rand_unit()) / (image_width - 1);
				double dy = (double) (j+rand_unit()) / (image_height - 1);

				ray r = camera_get_ray(&cam, dx, dy);
				total_color = vec3_add(2, total_color, test_color(&r, MAX_DEPTH));
			}
			vec3_print_color(vec3_scaled(total_color, 1.0 / SAMPLES_PER_PIXEL));
		}
	}
}

int scatter(ray* in_ray, hit_record* hr, vec3* attenuation, ray* scattered)
{
	vec3 diffuse_dir = vec3_add(2, hr->normal, vec3_random_unit());
	vec3 reflected_dir = vec3_reflected(in_ray->direction, hr->normal);

	vec3 scatter_dir = vec3_add(2, vec3_scaled(diffuse_dir, 1-hr->mat.metalicity), vec3_scaled(reflected_dir, hr->mat.metalicity));
	
	if(vec3_length_squared(scatter_dir) < 0.000001)
	{
		scatter_dir = hr->normal;
	}

	ray scatter_ray = ray_construct(hr->point, scatter_dir);
	*scattered = scatter_ray;
	*attenuation = hr->mat.color;

	return 1;
}

vec3 test_color(ray* r, int depth)
{
	if(depth <= 0)
		return vec3_construct(0,0,0);

	hit_record hit;
	hit.t = MAX_DIST;
	for(int i=0; i < object_count ; i++)
	{
		hit_record h = (*object_functions[i])(objects[i], r, 0.0001, MAX_DIST);
		if(hit.t < 0)
			hit = h;
		if(h.t > 0 && h.t < hit.t)
			hit = h;
	}
	
	if(hit.t < MAX_DIST)
	{
		vec3 atten;
		ray scattered;
		if(scatter(r, &hit, &atten, &scattered))
		{
			vec3 scat_col = test_color(&scattered, depth - 1);
			return vec3_construct(atten.x*scat_col.x, atten.y*scat_col.y, atten.z*scat_col.z);
		}
		//vec3 next_target = vec3_add(3, hit.point, hit.normal, vec3_random_unit());
		//ray next_ray = ray_construct(hit.point,vec3_subtract(next_target, hit.point));
		//return vec3_scaled(test_color(&next_ray, depth-1), 0.5);
		return vec3_construct(0,0,0);
	}

	// Background
	vec3 unit_dir = vec3_normalized(r->direction);
	double fade = 0.5 * (1 + unit_dir.y);
	return vec3_construct(fade, fade, 1);
}