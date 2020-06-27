#pragma once
#include "../commons/Debug.hpp"
#include "../commons/GLlibs.hpp"
#include "shader/Shader.hpp"
#include "model/Triangle.hpp"
#include "texture/Texture.hpp"
#include "model/ObjModel.hpp"
#include "../Application.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>


class Renderer {
public:
	static void init() {
		GLCall(glEnable(GL_DEPTH_TEST));
		Application::getLastInstance()->shader = new Shader("./res/shader/vertex.vert", "./res/shader/fragment.frag");
	}

	static void render() {

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glClearColor(0.15F, 0.15F, 0.15F, 0.0F));
		
		auto mvp = Application::getLastInstance()->getWindow()->getProjectionMatrix();
		mvp *= Application::getLastInstance()->getViewMatrix();

		if (Application::getLastInstance()->model) {
			mvp *= Application::getLastInstance()->model->getModelMatrix();
		}

		if (Application::getLastInstance()->shader) {
			Application::getLastInstance()->shader->Bind();
			Application::getLastInstance()->shader->SetUniform1i("textureColor", 0);
			Application::getLastInstance()->shader->SetUniform1i("textureNormal", 1);
			Application::getLastInstance()->shader->SetUniformMat4f("mvpMatrix", mvp);
			if (Application::getLastInstance()->model) {
				Application::getLastInstance()->shader->SetUniformMat4f("modelMatrix", Application::getLastInstance()->model->getModelMatrix());
			}

			auto& vp = Application::getLastInstance()->viewPos;
			Application::getLastInstance()->shader->SetUniform3f("viewPos", vp.x, vp.y, vp.z);
			
			Application::getLastInstance()->shader->SetUniform1i("lightCount", Application::getLastInstance()->lightPos.size());

			for (int i = 0; i < Application::getLastInstance()->lightPos.size(); ++i) {

				std::string posString = "lightPos[" + std::to_string(i) + "]";
				std::string colString = "lightCol[" + std::to_string(i) + "]";

				auto& lp = Application::getLastInstance()->lightPos[i];
				Application::getLastInstance()->shader->SetUniform3f(posString.c_str(), lp.x, lp.y, lp.z);
				auto& lc = Application::getLastInstance()->lightCol[i];
				Application::getLastInstance()->shader->SetUniform3f(colString.c_str(), lc.r, lc.g, lc.b);
			}

		}

		if (Application::getLastInstance()->textureColor) {
			Application::getLastInstance()->textureColor->Bind(0);
		}
		if (Application::getLastInstance()->textureNormal) {
			Application::getLastInstance()->textureNormal->Bind(1);
		}

		if (Application::getLastInstance()->model) {
			Application::getLastInstance()->model->render();
		}
	}

	static void end() {

	}
};
