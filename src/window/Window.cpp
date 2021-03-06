#include "Window.hpp"
#include <stdexcept>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error %d: %s\n", error, description);
}

Window::Window(int width, int height, const char* title, bool fullscreen) {

	glfwSetErrorCallback(error_callback);

	if (glfwInit() != GLFW_TRUE) {
		throw new std::runtime_error("Failed to initialize GLFW!");
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_GLFWwindow = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (!m_GLFWwindow) {
		throw new std::runtime_error("Failed to create window!");
	}

	glfwMakeContextCurrent(m_GLFWwindow);

	if (glewInit() != GLEW_OK) {
		throw new std::runtime_error("Failed to initialize GLEW!");
	}

	glViewport(0, 0, width, height);

	this->m_EventListener = new EventListener(this);
}

void Window::setResolution(int width, int height) {
	glfwSetWindowSize(m_GLFWwindow, width, height);
}

void Window::setFullscreen(bool fullscreen) {
	// If we have to change state
	if (this->getFullscreen() != fullscreen) {
		if (fullscreen) {

			GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_GLFWwindow, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);

		} else {

			int width;
			int height;
			glfwGetWindowSize(m_GLFWwindow, &width, &height);
			glfwSetWindowMonitor(m_GLFWwindow, fullscreen ? glfwGetPrimaryMonitor() : NULL, 100, 100, width, height, GLFW_DONT_CARE);

		}
	}
}

int Window::getWidth() {
	int width;
	glfwGetWindowSize(m_GLFWwindow, &width, nullptr);
	return width;
}

int Window::getHeight() {
	int height;
	glfwGetWindowSize(m_GLFWwindow, nullptr, &height);
	return height;
}

bool Window::getFullscreen() {
	return glfwGetWindowMonitor(m_GLFWwindow) != nullptr;
}

void Window::pollEvents() {
	glfwPollEvents();
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(m_GLFWwindow);
}

void Window::swapBuffers() {
	glfwSwapBuffers(m_GLFWwindow);
}

void Window::makeContextCurrent() {
	glfwMakeContextCurrent(m_GLFWwindow);
}

glm::mat4x4 Window::getProjectionMatrix() {
	return glm::perspective(3.14F/3, (float)getWidth()/getHeight(), 0.1F, 100.0F);
}

EventListener* Window::getEventListener() {
	return m_EventListener;
}

GLFWwindow* Window::getGLFWWindow() {
	return this->m_GLFWwindow;
}

Window::~Window() {
	glfwDestroyWindow(m_GLFWwindow);
	delete m_EventListener;
}
