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

