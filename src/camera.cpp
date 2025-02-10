#include "camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 _front, glm::vec3 _up)
{
    position = _position;
    front = _front;
    up = _up;
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 direction = glm::normalize(position - target);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(worldUp, direction));
    glm::vec3 up = glm::cross(direction, right);
}

void Camera::update()
{
    view = glm::lookAt(position, position + front, up);
}
