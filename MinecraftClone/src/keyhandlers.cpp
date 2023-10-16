#include "input.hpp"
#include "window.hpp"
#include <iostream>

void Input::bindAllKeyHandlers() {
	keyMap[GLFW_KEY_W] = [this]() { handleKeyW(); };
	keyMap[GLFW_KEY_A] = [this]() { handleKeyA(); };
	keyMap[GLFW_KEY_S] = [this]() { handleKeyS(); };
    keyMap[GLFW_KEY_D] = [this]() { handleKeyD(); };
	keyMap[GLFW_KEY_ESCAPE] = [this]() { handleKeyEsc(); };
	keyMap[GLFW_KEY_F11] = [this]() { handleKeyF11(); };
	keyMap[GLFW_KEY_LEFT_SHIFT] = [this]() { handleKeyLeftShift(); };
}

void Input::handleKeyEsc() {
	glfwSetWindowShouldClose(windowPtr->getWindowPointer(), GL_TRUE);
}
void Input::handleKeyF11() {
	windowPtr->toggleFullscreen();
}
void Input::handleKeyW() {
	std::cout << "Key W pressed\n";
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