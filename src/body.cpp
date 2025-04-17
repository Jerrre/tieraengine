#include "body.h"
#include "shader.h"
#include "mesh.h"
#include "global.h"

Body::Body()
{
}

void Body::set_scale(float newScale)
{
    scale = newScale;
    for (int m = 0; m < meshes.size(); m++) {
        meshes[m].model = glm::scale(meshes[m].model, glm::vec3(scale));
    }
    for (int c = 0; c < colliders.size(); c++) {
        colliders[c].min *= glm::vec3(scale);
        colliders[c].max *= glm::vec3(scale);
    }
}

void Body::draw(Shader& shader, Color color, glm::mat4 view, glm::mat4 projection)
{
    for (int m = 0; m < meshes.size(); m++) {
        meshes[m].draw(shader, color, view, projection);
    }
}
