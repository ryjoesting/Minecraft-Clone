#include "input.hpp"
#include <iostream>

Input::Input(Window* inWindow) { //Input Constructor
    windowPtr = inWindow;
    cameraPtr = nullptr;
    bindAllKeyHandlers();
}
Input::~Input() {
    std::cout << "Destroyed Input object successfully\n";
}

void Input::SetCameraPtr(Camera* ptr) {
    cameraPtr = ptr;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (keyMap.find(key) != keyMap.end()) {
            keyMap[key](); // Call the function
        }
        else {
            std::cout << "No function found for key " << key << std::endl;
        }
    }
}


void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    // Handle mouse button events
    if (action == GLFW_PRESS) {
        // Mouse button is pressed
    }
    else if (action == GLFW_RELEASE) {
        // Mouse button is released
    }
}

void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    // Handle scroll events
    // xOffset and yOffset represent the amount of scroll in the x and y directions, respectively
}

void Input::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Window* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (userWindow) {
        userWindow->setFramebufferSize(width, height);

        // Recenter the viewport
        int viewportWidth = userWindow->getWindowedWidth();
        int viewportHeight = userWindow->getWindowedHeight();
        int viewportX = (width - viewportWidth) / 2;
        int viewportY = (height - viewportHeight) / 2;

        glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    }
    std::cout << "Framebuffer = Width: " << width << "  Height: " << height << std::endl;
}

void Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    Window* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    userWindow->setMousePosX(xpos);
    userWindow->setMousePosY(ypos);
    //std::cout << "Mouse X: " << userWindow->getMousePosX() << "  Mouse Y: " << userWindow->getMousePosY() << std::endl;
}

