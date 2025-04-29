#include "physics.h"
#include "body.h"

Physics::Physics()
{
}

bool Physics::is_sphere_colliding(Sphere sphere1, Sphere sphere2)
{
    unsigned int dist = glm::length(sphere1.pos - sphere2.pos);
    if (dist <= sphere1.rad + sphere2.rad) {
        return true;
    }
	return false;
}

bool Physics::is_aabb_colliding(Box box1, Box box2)
{
    return (box1.min.x <= box2.max.x && box1.max.x >= box2.min.x &&
            box1.min.y <= box2.max.y && box1.max.y >= box2.min.y &&
            box1.min.z <= box2.max.z && box1.max.z >= box2.min.z);
}

bool Physics::static_collision(Body body)
{
    bool colliding = false;
    for (int i = 0; i < static_box_colliders->size(); i++) {
        if (is_aabb_colliding(body.colliders[0], static_box_colliders->at(i))) { // assume the moving body has only one collider
            colliding = true;
            break;
        }
        else {
            colliding = false;
        }
    }
    return colliding;
}
