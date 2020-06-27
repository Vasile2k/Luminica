#pragma once

#include "window/Window.hpp"
#include "render/shader/Shader.hpp"
#include "render/texture/Texture.hpp"
#include "render/model/ObjModel.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

class Application {
public:
	Application();
	~Application();

	void run();

	Window* getWindow();

	glm::mat4x4 getViewMatrix();

	static Application* getLastInstance();

	Shader* shader;
	ObjModel* model;
	Texture* textureColor;
	Texture* textureNormal;

	glm::vec3 viewPos;

	std::vector<glm::vec3> lightPos;
	std::vector<glm::vec3> lightCol;

private:
	Window* m_Window;
	static Application* lastInstance;

};

