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

    void handleKeyW();
    void handleKeyA();
    void handleKeyS();
    void handleKeyD();
    void handleKeyEsc();
    void handleKeyF11();
    void handleKeyLeftShift();
    void handleKeySpace();
    void handleKeyF2();
public:
    Input();
    ~Input();
    
    static std::unordered_map<int, std::pair<std::function<void()>, bool>> keyMap;

    void SetCameraPtr(Camera* ptr);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    
};
