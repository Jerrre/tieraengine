#include "physics.h"

bool is_sphere_colliding(Sphere sphere1, Sphere sphere2)
{
    unsigned int dist = glm::length(sphere1.pos - sphere2.pos);
    if (dist <= sphere1.rad + sphere2.rad) {
        return true;
    }
	return false;
}

bool is_aabb_colliding(Box box1, Box box2)
{
    return (box1.min.x <= box2.max.x && box1.max.x >= box2.min.x &&
            box1.min.y <= box2.max.y && box1.max.y >= box2.min.y &&
            box1.min.z <= box2.max.z && box1.max.z >= box2.min.z);
}
