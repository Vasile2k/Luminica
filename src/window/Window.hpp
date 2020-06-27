#pragma once
#include "../commons/GLlibs.hpp"
#include "Common.hpp"
#include "EventListener.hpp"
#include <glm/mat4x4.hpp>

class Window {

private:

	GLFWwindow* m_GLFWwindow;
	EventListener* m_EventListener;

public:
	Window(int width, int height, const char* title, bool fullscreen = false);
	void setResolution(int width, int height);
	void setFullscreen(bool fullscreen);
	int getWidth();
	int getHeight();
	bool getFullscreen();
	void pollEvents();
	bool shouldClose();
	void swapBuffers();
	void makeContextCurrent();
	glm::mat4x4 getProjectionMatrix();
	EventListener* getEventListener();
	GLFWwindow* getGLFWWindow();
	~Window();

	friend class EventListener;
	friend class GlobalGLFWEventHandler;

};
