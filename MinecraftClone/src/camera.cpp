#include "graphics.hpp"
/*In this modified code, the Camera class is responsible for managing the camera position,
orientation, and providing the view matrix through the getViewMatrix function.*/
Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
    : position(position), target(target), up(up), yaw(0.0f), pitch(0.0f) {
    updateViewMatrix();
}

void Camera::rotate(float deltaX, float deltaY) {
    float sensitivity = 0.2f; // Adjust this value to control the camera rotation speed

    // Calculate the change in yaw (horizontal rotation)
    float yawOffset = deltaX * sensitivity;

    // Calculate the change in pitch (vertical rotation)
    float pitchOffset = deltaY * sensitivity;

    // Update the camera's yaw and pitch
    yaw += yawOffset;
    pitch += pitchOffset;

    // Clamp the pitch to avoid over-rotation (optional)
    /*float maxPitch = 89.0f;
    if (pitch > maxPitch)
        pitch = maxPitch;
    else if (pitch < -maxPitch)
        pitch = -maxPitch;*/

    // Update the target position based on the new orientation
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target = glm::normalize(front);
    
    // Update the view matrix
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}
void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, target, up);
}