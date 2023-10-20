#pragma once
#include "camera.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "globals.hpp"

class Render {
private:
	
public:
	Render();
	void DrawScence();
};

////////////////////////
Render::Render() {
	std::cout << "Initialized Render object successfully" << std::endl;
}

void Render::DrawScence() {
	
}