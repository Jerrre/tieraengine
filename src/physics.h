#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <vector>

#include "global.h"

class Body;

class Physics {
public:
    Physics();
    std::vector<Box> *static_box_colliders;
    bool static_collision(Body body);
private:
    bool is_sphere_colliding(Sphere sphere1, Sphere sphere2);
    bool is_aabb_colliding(Box box1, Box box2);
};

#endif PHYSICS_H