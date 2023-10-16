#include "camera.hpp"
#include <iostream>
// Constructor with vectors
Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Position(position),
    WorldUp(up), Yaw(YAW), Pitch(PITCH) // Vars are globally defined in camera.hpp
{
    updateCameraVectors();
}

Camera::~Camera() {
    std::cout << "Destroyed Camera object successfully" << std::endl;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}




//void Camera::ProcessKeyboard(Camera_Movement direction)
//{
//    float velocity = MovementSpeed * windowPtr->deltaTime;
//    if (direction == FORWARD)
//        Position += Front * velocity;
//    if (direction == BACKWARD)
//        Position -= Front * velocity;
//    if (direction == LEFT)
//        Position -= Right * velocity;
//    if (direction == RIGHT)
//        Position += Right * velocity;
//}