#pragma once
#include "camera.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "globals.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "block.hpp"

class Scene {
private:
	glm::vec3 cubePositions[10];

	void updateDeltaTime();
	void DrawAllBlocks();
	void DrawBlock();
	void DrawBlockTop();
	void DrawBlockSides();
	void DrawBlockBottom();
public:
	Scene();
	void Render();
};

////////////////////////
Scene::Scene() :
	cubePositions {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  -1.0f),
		glm::vec3(0.0f,  0.0f,  -1.0f),
		glm::vec3(1.0f,  0.0f,  -1.0f),
		glm::vec3(-1.0f,  0.0f,  1.0f),
		glm::vec3(0.0f,  0.0f,  1.0f),
		glm::vec3(1.0f,  0.0f,  1.0f),
		glm::vec3(4.0f,  4.0f,  -4.0f)
}
{
	std::cout << "Initialized Scene object successfully" << std::endl;
}
void Scene::DrawAllBlocks() {
	for (auto& pos : cubePositions) {
		Block block(GRASS, pos);
	}
}
void Scene::DrawBlock() {

}
void Scene::DrawBlockTop(){
}
void Scene::DrawBlockSides(){
}
void Scene::DrawBlockBottom(){
}
void Scene::Scene::updateDeltaTime() {
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	Globals::shaderPtr->bind();
} 