#include "body.h"

Body::Body()
{
}

void Body::update(glm::vec3 new_position)
{
    position = new_position;
    for (int c = 0; c < colliders.size(); c++) {
        colliders[c].min = position;
        colliders[c].max = colliders[c].min + glm::vec3(collider_size);
    }
}
