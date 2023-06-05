#include "input.hpp"
#include "window.hpp"
#include <iostream>

void Input::bindAllKeyHandlers() {
    keyMap[GLFW_KEY_A] = [this]() { handleKeyA(); };
	keyMap[GLFW_KEY_ESCAPE] = [this]() { handleKeyEsc(); };
	keyMap[GLFW_KEY_F11] = [this]() { handleKeyF11(); };
}

void Input::handleKeyEsc() {
	glfwSetWindowShouldClose(inputWindow->getWindowPointer(), GL_TRUE);
}
void Input::handleKeyF11() {
	inputWindow->toggleFullscreen();
}
void Input::handleKeyA() {
	std::cout << "Key A pressed\n";
}