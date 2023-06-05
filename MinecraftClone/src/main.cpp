#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "input.hpp"
#include "shader.hpp"
#include "window.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "graphics.hpp"
#include "cube.hpp"
std::unordered_map<int, std::function<void()>> Input::keyMap;

int main() {
    Window myWindow(3,3); //defaults to OpenGL core 3.3
    glfwSetWindowUserPointer(myWindow.getWindowPointer(), &myWindow);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Input input(&myWindow);
    
    Shader shaderProgram("src/shaders/vertex.vert", "src/shaders/fragment.frag"); //took a while to figure the correct path.
    /*
    //want to draw a square to the screen using index buffer.
    float vertices[] = {
        // Front face
        -0.5f, -0.5f, 0.5f,  // Bottom-left 0
        0.5f, -0.5f, 0.5f,   // Bottom-right 1
        0.5f, 0.5f, 0.5f,    // Top-right 2
        -0.5f, 0.5f, 0.5f,   // Top-left 3

        // Back face
        -0.5f, -0.5f, -0.5f, // Bottom-left 4
        0.5f, -0.5f, -0.5f,  // Bottom-right 5
        0.5f, 0.5f, -0.5f,   // Top-right 6
        -0.5f, 0.5f, -0.5f  // Top-left 7
    };

    unsigned int indices[] = {
        // Front face
        0, 1, 2,    // Triangle 1
        2, 3, 0,    // Triangle 2
        // Back face
        4, 5, 6,    // Triangle 1
        6, 7, 4,     // Triangle 2
        // Left face
        3, 7, 4,    // Triangle 1
        4, 0, 3,    // Triangle 2
        // Right face
        1, 5, 6,    // Triangle 1
        6, 2, 1 ,    // Triangle 2
        // Top face
        3, 2, 6,    // Triangle 1
        6, 7, 3,    // Triangle 2
        // Bottom face
        4, 5, 1,
        1, 0, 4
    };

    //Vertex Buffer Object (VBO)
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    */
    Cube originCube(glm::vec3(0.0f, 0.0f, 0.0f));

    // Create a Renderer object
    Renderer renderer(myWindow.getFramebufferWidth(), myWindow.getFramebufferHeight());

    // Create a Camera object
    glm::vec3 cameraEye(0.0f, 5.0f, 7.0f);
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
    Camera camera(cameraEye, cameraTarget, cameraUp);

    // Set up the transformation matrix
    glm::vec3 scale(1.0f);
    glm::vec3 position(0.0f, 0.0f, 0.0f);
    float rotation = 0.0f;
    glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), position);
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    transformationMatrix = glm::scale(transformationMatrix, scale);

    // Get the view matrix from the camera
    glm::mat4 viewMatrix = camera.getViewMatrix();

    // Get the projection matrix from the renderer
    glm::mat4 projectionMatrix = renderer.getProjectionMatrix();

    // Combine the matrices
    //glm::mat4 mvp = projectionMatrix * viewMatrix * transformationMatrix;
    shaderProgram.bind();
    glm::mat4 mvp = projectionMatrix * viewMatrix * transformationMatrix;
    // Pass the MVP matrix to the shader
    shaderProgram.uploadMat4("uMVP", mvp);

    // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
    //Main render loop
    glEnable(GL_DEPTH_TEST);

    double mouseX = 0, mouseY = 0;
    glfwGetCursorPos(myWindow.getWindowPointer(), &mouseX, &mouseY);
    
    double deltaX = 0;
    double deltaY = 0;
    double lastMouseX = mouseX;
    double lastMouseY = mouseY;

    while (!glfwWindowShouldClose(myWindow.getWindowPointer()))
    {
        // Clear the color and depth buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //---
        // Mouse input
        glfwGetCursorPos(myWindow.getWindowPointer(), &mouseX, &mouseY);

        // Calculate mouse movement
        deltaX = mouseX - lastMouseX;
        deltaY = -(mouseY - lastMouseY);

        // Update the camera orientation based on mouse movement
        camera.rotate(deltaX, deltaY);

        // Update the last known mouse position
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        //---
        // Update the rotation angle
        rotation = 0.0f;
        //rotation += 0.2f;

        // Update the transformation matrix
        glm::mat4 transformationMatrix = glm::translate(glm::mat4(1.0f), position);
        transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        transformationMatrix = glm::scale(transformationMatrix, scale);

        // Get the view matrix from the camera
        glm::mat4 viewMatrix = camera.getViewMatrix();

        // Combine the matrices
        glm::mat4 mvp = projectionMatrix * viewMatrix * transformationMatrix;

        // Pass the MVP matrix to the shader
        shaderProgram.uploadMat4("uMVP", mvp);

        // Render the cube
        shaderProgram.bind();
        glBindVertexArray(originCube.getVAO());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(myWindow.getWindowPointer());
        glfwPollEvents();
    }

    originCube.~Cube();
    //Clear allocated memory
   
	return 0;
}