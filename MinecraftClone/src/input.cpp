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
    if (action == GLFW_REPEAT) {
        if (keyMap.find(key) != keyMap.end()) {
            keyMap[key].first(); // Call the function
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

///////////////////////////////////////////////////////////////////////////////////////////////////
// Begin keyhandlers

void Input::bindAllKeyHandlers() {
    keyMap[GLFW_KEY_W] = std::make_pair([this]() { handleKeyW(); }, false);
    keyMap[GLFW_KEY_A] = std::make_pair([this]() { handleKeyA(); }, false);
    keyMap[GLFW_KEY_S] = std::make_pair([this]() { handleKeyS(); }, false);
    keyMap[GLFW_KEY_D] = std::make_pair([this]() { handleKeyD(); }, false);
    keyMap[GLFW_KEY_ESCAPE] = std::make_pair([this]() { handleKeyEsc(); }, false);
    keyMap[GLFW_KEY_F11] = std::make_pair([this]() { handleKeyF11(); }, false);
    keyMap[GLFW_KEY_LEFT_SHIFT] = std::make_pair([this]() { handleKeyLeftShift(); }, false);
}

void Input::handleKeyEsc() {
    glfwSetWindowShouldClose(windowPtr->getWindowPointer(), GL_TRUE);
}
void Input::handleKeyF11() {
    windowPtr->toggleFullscreen();
}
void Input::handleKeyW() {
    std::cout << "Key W pressed\n";
    cameraPtr->Position += windowPtr->cameraSpeed * cameraPtr->Front;
}
void Input::handleKeyA() {
    std::cout << "Key A pressed\n";
}
void Input::handleKeyS() {
    std::cout << "Key S pressed\n";
}
void Input::handleKeyD() {
    std::cout << "Key D pressed\n";
}
void Input::handleKeyLeftShift() {
    if (glfwGetInputMode(windowPtr->getWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        glfwSetInputMode(windowPtr->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (glfwGetInputMode(windowPtr->getWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(windowPtr->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    std::cout << "Toggled cursor mode\n";
}