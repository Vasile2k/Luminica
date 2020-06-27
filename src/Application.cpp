#include "Application.hpp"
#include <chrono>
#include "render/Renderer.hpp"
#include "render/GuiRenderer.hpp"

Application* Application::lastInstance = nullptr;

std::chrono::milliseconds getCurrentTime() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

Application::Application() : viewPos(-6.0F, 4.0F, 1.0F) {
	shader = nullptr;
	model = nullptr;
	textureColor = nullptr;
	textureNormal = nullptr;

	lightPos.push_back(glm::vec3(-2.0F, 4.0F, 6.0F));
	lightCol.push_back(glm::vec3(1.0F, 1.0F, 1.0F));

	m_Window = new Window(1280, 720, "P-teu");
	lastInstance = this;
	Renderer::init();
	GuiRenderer::init();
}

Application::~Application() {
	delete m_Window;
	GuiRenderer::end();
	Renderer::end();

	if (shader) {
		delete shader;
	}

	if (model) {
		delete model;
	}

	if (textureColor) {
		delete textureColor;
	}

	if (textureNormal) {
		delete textureNormal;
	}
}

void Application::run() {
	m_Window->makeContextCurrent();

	std::chrono::milliseconds currentTime = getCurrentTime();

	while (!m_Window->shouldClose()) {

		//std::chrono::milliseconds now = getCurrentTime();

		Renderer::render();
		GuiRenderer::render();

		//currentTime = now;

		m_Window->swapBuffers();
		m_Window->pollEvents();
	}
}

Window* Application::getWindow() {
	return this->m_Window;
}

glm::mat4x4 Application::getViewMatrix() {
	return glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

Application* Application::getLastInstance() {
	return lastInstance;
}
