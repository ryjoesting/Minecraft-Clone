#pragma once
#include "window.hpp"
#include <unordered_map>
#include <map>
#include <functional>
#include <iostream>
#include "camera.hpp"

class Input {
private:
    
    void bindAllKeyHandlers();

public:
    Input();
    ~Input();
    
    void SetCameraPtr(Camera* ptr);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    static void handleKeyW();
    static void handleKeyA();
    static void handleKeyS();
    static void handleKeyD();
    static void handleKeyEsc();
    static void handleKeyF11();
    static void handleKeyLeftShift();
    static void handleKeySpace();
    static void handleKeyF2();
};
