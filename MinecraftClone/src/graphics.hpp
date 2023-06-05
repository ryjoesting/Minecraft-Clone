#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer {
private:
    glm::mat4 projectionMatrix;

public:
    Renderer(float screenWidth, float screenHeight);
    glm::mat4 getModelViewProjectionMatrix(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix) const;
    glm::mat4 getProjectionMatrix() const;
};

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
