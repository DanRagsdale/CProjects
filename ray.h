#pragma once

#include "vec3.h"

typedef struct ray {
	vec3 origin;
	vec3 direction;
} ray;

// Util functions
ray ray_construct(vec3 origin, vec3 direction);

vec3 ray_at(ray* r, double t);