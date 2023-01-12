#pragma once

typedef struct vec3 {
	double x, y, z;
} vec3;

// Util functions
vec3 vec3_construct(double x, double y, double z);
vec3 vec3_random_in_unit_sphere();
vec3 vec3_random_unit();

// General vec3 operations 
double vec3_length(vec3 input);
double vec3_length_squared(vec3 input);
double vec3_dot(vec3 A, vec3 B);
vec3 vec3_add(int count,...);
vec3 vec3_subtract(vec3 A, vec3 B);
vec3 vec3_scaled(vec3 input, double t);
vec3 vec3_normalized(vec3 input);

// Color functions
void vec3_print_color(vec3 input);