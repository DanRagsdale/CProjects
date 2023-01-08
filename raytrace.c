// Working through the raytracing in one weekend git book as a way to learn graphics and C
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

#include <stdio.h>
#include <math.h>

#include "vec3.h"
#include "ray.h"

int main() 
{
	const int image_width = 256;
	const int image_height = 256;

	ray test_ray;
	test_ray.origin = vec3_construct(0,0,0);
	test_ray.direction = vec3_construct(1,1,0);
	vec3 at = ray_at(&test_ray, 2);
	fprintf(stderr, "%f, %f, %f", at.x, at.y, at.z);



	printf("P3\n%d %d\n255\n", image_width, image_height);

	for(int j = image_height-1; j >= 0; j--)
	{
		for(int i = image_width-1; i >= 0; i--)
		{
			vec3 color;
			color.x = (double) i / (image_width-1);
			color.y  = (double) j / (image_height-1);
			color.z = 0.8;

			vec3_print_color(color);
		}
	}
}