#include "camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 _front, glm::vec3 _up)
{
    position = _position;
    front = _front;
    up = _up;
}

void Camera::update(glm::vec2 mouseOffset)
{
    yaw += mouseOffset.x;
    pitch += mouseOffset.y;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    view = glm::lookAt(position, position + front, up);
}
