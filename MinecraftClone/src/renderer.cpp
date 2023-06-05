#include "graphics.hpp"
/*The Renderer class focuses on managing the projection matrix and provides the getModelViewProjectionMatrix 
function, which takes the model matrix and the view matrix as inputs and returns the combined MVP matrix.*/
Renderer::Renderer(float screenWidth, float screenHeight) {
    // Set up default projection matrix
    float fov = 70.0f;
    float aspectRatio = screenWidth / screenHeight;
    float near = 0.1f;
    float far = 1000.0f;
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}
glm::mat4 Renderer::getProjectionMatrix() const {
    return projectionMatrix;
}
glm::mat4 Renderer::getModelViewProjectionMatrix(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix) const {
    return projectionMatrix * viewMatrix * modelMatrix;
}
