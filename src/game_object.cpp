#include "game_object.h"
#include "shader.h"
#include "mesh.h"

GameObject::GameObject()
{
    
}

void GameObject::set_scale(float newScale)
{
    scale = newScale;
    for (int m = 0; m < meshes.size(); m++) {
        meshes[m].model = glm::scale(meshes[m].model, glm::vec3(scale));
    }
    for (int c = 0; c < body.colliders.size(); c++) {
        body.colliders[c].min *= glm::vec3(scale);
        body.colliders[c].max *= glm::vec3(scale);
    }
}

void GameObject::draw(Shader& shader, Color color, glm::mat4 view, glm::mat4 projection)
{
    for (int m = 0; m < meshes.size(); m++) {
        meshes[m].draw(shader, color, view, projection);
    }
}

void GameObject::update()
{
    body.update(position);
}