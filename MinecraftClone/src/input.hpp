#pragma once
#include "window.hpp"
#include <unordered_map>
#include <map>
#include <functional>
#include <iostream>
//using KeyCallback = void (*)(GLFWwindow*, int, int, int, int);

class Input {
private:
    static std::unordered_map<int, std::function<void()>> keyMap;
    Window* inputWindow;

    void bindAllKeyHandlers();

    
    void handleKeyA();
    void handleKeyEsc();
    void handleKeyF11();
    
public:
    Input(Window* inWindow);
    ~Input();
    
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

    
};
