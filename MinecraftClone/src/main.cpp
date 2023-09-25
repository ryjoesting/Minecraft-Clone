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
#include "cube.hpp"

std::unordered_map<int, std::function<void()>> Input::keyMap;

void catchGLError(Window* window);

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
    
    Cube myCube(glm::vec3(0.0f));

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
    //Main render loop
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(myWindow.getWindowPointer()))
    {
        // Clear the color and depth buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render the cube
        shaderProgram.bind();
        glBindVertexArray(myCube.getVAO());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);

        // Swap buffers and poll events, raise errors
        catchGLError(&myWindow);
        glfwSwapBuffers(myWindow.getWindowPointer());
        glfwPollEvents();
    }
   
	return 0;
}
void catchGLError(Window* window) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        switch (errorCode) {
        case GL_INVALID_ENUM:
            std::cout << "OpenGL Error: GL_INVALID_ENUM" << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cout << "OpenGL Error: GL_INVALID_VALUE" << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cout << "OpenGL Error: GL_INVALID_OPERATION" << std::endl;
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << "OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cout << "OpenGL Error: GL_OUT_OF_MEMORY" << std::endl;
            break;
        default:
            std::cout << "OpenGL Error: Unknown error code" << std::endl;
            break;
        }
    }

    // Optionally, you can set a flag to close the window if an error occurred:
    if (errorCode != GL_NO_ERROR) {
        glfwSetWindowShouldClose(window->getWindowPointer(), GL_TRUE);
    }
}
