// Working through the raytracing in one weekend git book as a way to learn graphics and C
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include <stdio.h>
#include <math.h>

#include "vec3.h"
#include "ray.h"

vec3 test_color(ray* r)
{
	vec3 unit_dir = vec3_normalized(r->direction);
	double fade = 0.5 * (1 + unit_dir.y);
	return vec3_construct(fade, fade, fade);
}

int main() 
{
	// Test Code
	ray test_ray;
	test_ray.origin = vec3_construct(0,0,0);
	test_ray.direction = vec3_construct(1,1,0);
	vec3 at = ray_at(&test_ray, 2);
	fprintf(stderr, "%f, %f, %f", at.x, at.y, at.z);

	// Image Setup
	const int image_width = 400;
	const int image_height = 200;

	// Camera Setup
	double viewport_height = 2.0;
	double viewport_width = 4.0;
	double focal_length = 1.0;

	vec3 origin = vec3_construct(0,0,0);
	vec3 horizontal = vec3_construct(viewport_width, 0, 0);
	vec3 vertical = vec3_construct(0, viewport_height, 0);

	vec3 lower_left = vec3_construct(-viewport_width / 2, -viewport_height / 2, -focal_length);

	// Render
	printf("P3\n%d %d\n255\n", image_width, image_height);

	for(int j = image_height-1; j >= 0; j--)
	{
		for(int i = image_width-1; i >= 0; i--)
		{
			double dx = (double) i / (image_width - 1);
			double dy = (double) j / (image_height - 1);

			ray r = ray_construct(origin, vec3_construct(lower_left.x + dx * horizontal.x, lower_left.y + dy * vertical.y, 0));
			vec3 color = test_color(&r);
			vec3_print_color(color);
		}
	}
}