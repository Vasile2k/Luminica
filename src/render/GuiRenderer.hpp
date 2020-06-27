#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../Application.hpp"

class GuiRenderer {
public:
	static void init() {
		IMGUI_CHECKVERSION();
		const char* glsl_version = "#version 130";

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(Application::getLastInstance()->getWindow()->getGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	static void render() {
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
		ImGui::Begin("Scene");

		ImGui::Text("View position");

		ImGui::SliderFloat("X", &Application::getLastInstance()->viewPos.x, -10.0F, 10.0F);
		ImGui::SliderFloat("Y", &Application::getLastInstance()->viewPos.y, -10.0F, 10.0F);
		ImGui::SliderFloat("Z", &Application::getLastInstance()->viewPos.z, -10.0F, 10.0F);

		ImGui::Text("Load a model");
		if (ImGui::Button("Load model")) {
			if (Application::getLastInstance()->model == nullptr) {
				Application::getLastInstance()->model = new ObjModel("./res/model/pear.obj");
			}
			if (Application::getLastInstance()->textureColor == nullptr) {
				Application::getLastInstance()->textureColor = new Texture("./res/texture/pear_diffuse.png");
			}
			if (Application::getLastInstance()->textureNormal == nullptr) {
				Application::getLastInstance()->textureNormal = new Texture("./res/texture/pear_normal.png");
			}
		}

		if (Application::getLastInstance()->model) {
			ImGui::SliderFloat("Object X", &Application::getLastInstance()->model->x, -10.0F, 10.0F);
			ImGui::SliderFloat("Object Y", &Application::getLastInstance()->model->y, -10.0F, 10.0F);
			ImGui::SliderFloat("Object Z", &Application::getLastInstance()->model->z, -10.0F, 10.0F);
		}

		if (ImGui::Button("Add light")) {
			if (Application::getLastInstance()->lightPos.size() < 16) {
				Application::getLastInstance()->lightPos.push_back(glm::vec3(0.0F));
				Application::getLastInstance()->lightCol.push_back(glm::vec3(1.0F));
			}
		}

		if (ImGui::Button("Remove light")) {
			if (!Application::getLastInstance()->lightPos.empty()) {
				Application::getLastInstance()->lightPos.pop_back();
				Application::getLastInstance()->lightCol.pop_back();
			}
		}

		for (int i = 0; i < Application::getLastInstance()->lightPos.size(); ++i) {
			ImGui::Text("Light position");

			std::string light = "Light " + std::to_string(i);

			ImGui::SliderFloat((light + " X").c_str(), &Application::getLastInstance()->lightPos[i].x, -10.0F, 10.0F);
			ImGui::SliderFloat((light + " Y").c_str(), &Application::getLastInstance()->lightPos[i].y, -10.0F, 10.0F);
			ImGui::SliderFloat((light + " Z").c_str(), &Application::getLastInstance()->lightPos[i].z, -10.0F, 10.0F);
			ImGui::ColorEdit3((light + " Color").c_str(), (float*)&Application::getLastInstance()->lightCol[i]);
		}



		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	static void end() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};
