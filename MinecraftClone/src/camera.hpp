#pragma once
#include <glm/glm.hpp>
class Camera {
private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 viewMatrix;

    float yaw;
    float pitch;

    void updateViewMatrix();

public:
    Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
    glm::mat4 getViewMatrix() const;

    void rotate(float deltaX, float deltaY);

};

