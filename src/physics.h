#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "global.h"

bool is_sphere_colliding(Sphere sphere1, Sphere sphere2);
bool is_aabb_colliding(Box box1, Box box2);

#endif PHYSICS_H