#include "input.hpp"
#include "window.hpp"
#include <iostream>

void Input::bindAllKeyHandlers() {
    keyMap[GLFW_KEY_A] = [this]() { handleKeyA(); };
	keyMap[GLFW_KEY_ESCAPE] = [this]() { handleKeyEsc(); };
	keyMap[GLFW_KEY_F11] = [this]() { handleKeyF11(); };
	keyMap[GLFW_KEY_LEFT_SHIFT] = [this]() { handleKeyLeftShift(); };
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
void Input::handleKeyLeftShift() {
	if (glfwGetInputMode(inputWindow->getWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
		glfwSetInputMode(inputWindow->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (glfwGetInputMode(inputWindow->getWindowPointer(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
		glfwSetInputMode(inputWindow->getWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	std::cout << "Toggled cursor mode\n";
}