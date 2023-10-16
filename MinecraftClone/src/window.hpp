#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	double mousePos_x;
	double mousePos_y;
	int framebufferWidth;
	int framebufferHeight;
	int windowed_xpos;
	int windowed_ypos;
	int windowed_width;
	int windowed_height;
	GLFWmonitor* monitor;
	const GLFWvidmode* mode;
	GLFWwindow* window;

	void toggleToWindowedMode();
	void toggleToFullscreenMode();

public:
	Window(int majorVersion, int minorVersion);
	~Window();
	void setInputCallbacks();
	bool getIsFullscreen() const;
	void toggleFullscreen();
	int getFramebufferHeight() const;
	int getFramebufferWidth() const;
	int getWindowedXPos() const;
	int getWindowedYPos() const;
	int getWindowedWidth() const;
	int getWindowedHeight() const;
	double getMousePosX() const;
	double getMousePosY() const;
	void setMousePosX(double x);
	void setMousePosY(double y);

	void catchGLError();

	GLFWwindow* getWindowPointer() const;
	const GLFWvidmode* getVidModePointer() const;
	GLFWmonitor* getMonitorPointer() const;

	void setFramebufferSize(int width, int height) {
		framebufferWidth = width;
		framebufferHeight = height;
	}
};