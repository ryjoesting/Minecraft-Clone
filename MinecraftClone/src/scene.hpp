#pragma once
#include "camera.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "globals.hpp"
#include "glad/glad.h"


class Scene {
private:
	void updateDeltaTime();
public:
	Scene();
	void Render();
};

////////////////////////
Scene::Scene() {
	std::cout << "Initialized Scene object successfully" << std::endl;
}
void Scene::updateDeltaTime() {
	float currentFrame = static_cast<float>(glfwGetTime());
	Globals::windowPtr->deltaTime = currentFrame - Globals::windowPtr->lastFrame;
	Globals::windowPtr->lastFrame = currentFrame;
	Globals::cameraPtr->MovementSpeed = 2.5 * (float)Globals::windowPtr->deltaTime;
} 
void Scene::Render() {
	updateDeltaTime();
	// Clear the color and depth buffers
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} 