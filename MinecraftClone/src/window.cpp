#include "window.hpp"
#include "input.hpp"
#include <iostream>

Window::Window(int majorVersion, int minorVersion)
    : framebufferWidth(0),
    framebufferHeight(0),
    windowed_xpos(0),
    windowed_ypos(0),
    windowed_width(0),
    windowed_height(0),
    monitor(nullptr),
    mode(nullptr),
    window(nullptr),
    mousePos_x(0), mousePos_y(0)
    {

    glfwInit();
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(mode->width, mode->height, "Minecraft Clone", NULL, NULL);

    glfwGetWindowPos(window, &windowed_xpos, &windowed_ypos);
    glfwGetWindowSize(window, &windowed_width, &windowed_height);

    setInputCallbacks();

    // Uncomment to disable cursor on startup (used for debugging)
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);
    std::cout << "Initialized Window class object successfully.\n";
}
Window::~Window() {
    glfwTerminate();
    std::cout << "Destroyed Window class object successfully.\n";
}

void Window::toggleFullscreen() {
    if (glfwGetWindowMonitor(window)) {
        toggleToWindowedMode();
    }
    else {
        toggleToFullscreenMode();
    }
}

void Window::toggleToWindowedMode() {
    glfwSetWindowMonitor(window, nullptr, windowed_xpos, windowed_ypos, windowed_width, windowed_height, 0);
}

void Window::toggleToFullscreenMode() {
    monitor = glfwGetPrimaryMonitor();
    if (monitor) {
        mode = glfwGetVideoMode(monitor);
        glfwGetWindowPos(window, &windowed_xpos, &windowed_ypos);
        glfwGetWindowSize(window, &windowed_width, &windowed_height);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
}

int Window::getFramebufferHeight() const {
    return framebufferHeight;
}

int Window::getFramebufferWidth() const {
    return framebufferWidth;
}

int Window::getWindowedXPos() const {
    return windowed_xpos;
}

int Window::getWindowedYPos() const {
    return windowed_ypos;
}

int Window::getWindowedWidth() const {
    return windowed_width;
}

int Window::getWindowedHeight() const {
    return windowed_height;
}
GLFWwindow* Window::getWindowPointer() const {
    return window;
}
const GLFWvidmode* Window::getVidModePointer() const {
    return mode;
}
GLFWmonitor* Window::getMonitorPointer() const {
    return monitor;
}

void Window::setInputCallbacks() {
    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
    glfwSetScrollCallback(window, Input::scrollCallback);
    glfwSetFramebufferSizeCallback(window, Input::framebufferSizeCallback);
    glfwSetCursorPosCallback(window, Input::cursorPositionCallback);
}
double Window::getMousePosX() const {
    return mousePos_x;
}
double Window::getMousePosY() const {
    return mousePos_y;
}
void Window::setMousePosX(double x) {
    mousePos_x = x;
}
void Window::setMousePosY(double y) {
    mousePos_y = y;
}
void Window::catchGLError() {
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
        glfwSetWindowShouldClose(this->getWindowPointer(), GL_TRUE);
    }
}