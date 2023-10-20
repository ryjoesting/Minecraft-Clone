#pragma once
#include "window.hpp"
#include "camera.hpp"
#include "shader.hpp"

class Globals {
public:
	static Window* windowPtr;
	static Camera* cameraPtr;
	static Shader* shaderPtr;

	static std::unordered_map<int, std::pair<std::function<void()>, bool>> keyMap;
};

