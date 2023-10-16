#include "input.hpp"
#include "window.hpp"
#include <iostream>

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