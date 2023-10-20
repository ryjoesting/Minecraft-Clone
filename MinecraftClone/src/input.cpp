#include <iostream>
#include "input.hpp"
#include "globals.hpp"

Input::Input(Window* inWindow) {
    bindAllKeyHandlers();
}
Input::~Input() {
    std::cout << "Destroyed Input object successfully\n";
}

void Input::SetCameraPtr(Camera* ptr) {
    Globals::cameraPtr = ptr;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) 
    {
        case GLFW_PRESS:
            if (keyMap.find(key) != keyMap.end()) {
                keyMap[key].second = true;
            }
            else {
                std::cout << "No function found for key " << key << " (press)" << std::endl;
            }
            break;
        case GLFW_RELEASE:
            if (keyMap.find(key) != keyMap.end()) {
                keyMap[key].second = false;
            }
            else {
                std::cout << "No function found for key " << key << " (release)" << std::endl;
            }
            break;
        default:
            break;
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
    //Window* userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    Globals::windowPtr->setMousePosX(xpos);
    Globals::windowPtr->setMousePosY(ypos);
    double xoffset = xpos - Globals::windowPtr->previous_mousePos_x;
    double yoffset = ypos - Globals::windowPtr->previous_mousePos_y;
    Globals::windowPtr->previous_mousePos_x = xpos;
    Globals::windowPtr->previous_mousePos_y = ypos;
    xoffset *= Globals::cameraPtr->MouseSensitivity;
    yoffset *= Globals::cameraPtr->MouseSensitivity;

    Globals::cameraPtr->Yaw += (float)xoffset;
    Globals::cameraPtr->Pitch += (float)yoffset * -1;
    
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Globals::cameraPtr->Pitch > 89.0f)
        Globals::cameraPtr->Pitch = 89.0f;
    if (Globals::cameraPtr->Pitch < -89.0f)
        Globals::cameraPtr->Pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    Globals::cameraPtr->updateCameraVectors();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Begin keyhandlers

void Input::bindAllKeyHandlers() {
    keyMap[GLFW_KEY_W] = std::make_pair([this]() { handleKeyW(); }, false);
    keyMap[GLFW_KEY_A] = std::make_pair([this]() { handleKeyA(); }, false);
    keyMap[GLFW_KEY_S] = std::make_pair([this]() { handleKeyS(); }, false);
    keyMap[GLFW_KEY_D] = std::make_pair([this]() { handleKeyD(); }, false);
    keyMap[GLFW_KEY_SPACE] = std::make_pair([this]() { handleKeySpace(); }, false);
    keyMap[GLFW_KEY_LEFT_SHIFT] = std::make_pair([this]() { handleKeyLeftShift(); }, false);
    keyMap[GLFW_KEY_ESCAPE] = std::make_pair([this]() { handleKeyEsc(); }, false);
    keyMap[GLFW_KEY_F11] = std::make_pair([this]() { handleKeyF11(); }, false);
    keyMap[GLFW_KEY_F2] = std::make_pair([this]() { handleKeyF2(); }, false);
}

void Input::handleKeyEsc() {
    glfwSetWindowShouldClose(Globals::windowPtr->getWindowPointer(), GL_TRUE);
}
void Input::handleKeyF2() {
    if (glfwGetInputMode(Globals::windowPtr->getWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        glfwSetInputMode(Globals::windowPtr->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (glfwGetInputMode(Globals::windowPtr->getWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        glfwSetInputMode(Globals::windowPtr->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    std::cout << "Toggled cursor mode\n";
}
void Input::handleKeyF11() {
    Globals::windowPtr->toggleFullscreen();
}
void Input::handleKeyW() {
    //std::cout << "Key W pressed\n";
    float temp = Globals::cameraPtr->Position.y;
    Globals::cameraPtr->Position += Globals::cameraPtr->MovementSpeed * Globals::cameraPtr->Front;
    Globals::cameraPtr->Position.y = temp;
}
void Input::handleKeyA() {
    //std::cout << "Key A pressed\n";
    float temp = Globals::cameraPtr->Position.y;
    Globals::cameraPtr->Position -= Globals::cameraPtr->MovementSpeed * Globals::cameraPtr->Right;
    Globals::cameraPtr->Position.y = temp;
}
void Input::handleKeyS() {
    //std::cout << "Key S pressed\n";
    float temp = Globals::cameraPtr->Position.y;
    Globals::cameraPtr->Position -= Globals::cameraPtr->MovementSpeed * Globals::cameraPtr->Front;
    Globals::cameraPtr->Position.y = temp;
}
void Input::handleKeyD() {
    //std::cout << "Key D pressed\n";
    float temp = Globals::cameraPtr->Position.y;
    Globals::cameraPtr->Position += Globals::cameraPtr->MovementSpeed * Globals::cameraPtr->Right;
    Globals::cameraPtr->Position.y = temp;
}
void Input::handleKeySpace() {
    Globals::cameraPtr->Position.y += Globals::cameraPtr->MovementSpeed;
}
void Input::handleKeyLeftShift() {
    Globals::cameraPtr->Position.y -= Globals::cameraPtr->MovementSpeed;
}