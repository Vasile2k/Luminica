#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "EntryPoint.hpp"

#define STB_IMAGE_IMPLEMENTATION
#pragma warning(push)
#pragma warning(disable:6011)
#pragma warning(disable:6262)
#pragma warning(disable:6308)
#pragma warning(disable:26451)
#pragma warning(disable:28128)
#pragma warning(disable:28182)
//#include "stb_image.h"
#pragma warning(pop)
#undef STB_IMAGE_IMPLEMENTATION

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


std::string readShader(const char *fn)
{
	std::ifstream ifile(fn);
	std::string filetext;
	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		filetext.append(line + "\n");
	}
	return filetext;
}

void updateInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error %d: %s\n", error, description);
}

bool loadShader(GLuint &program) {
	GLint success;
	char infoLog[512];


	std::string vertTempSrc = readShader("D:\\Downloads\\Github\\Luminica\\res\\shaders\\fragment.glsl");
	const GLchar* vertSrc = vertTempSrc.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Could not compile vertex shader: " << std::endl;
		std::cout << infoLog << std::endl;
		return false;
	}

	std::string fragTempSrc = readShader("D:\\Downloads\\Github\\Luminica\\res\\shaders\\fragment.glsl");
	const GLchar* fragSrc = fragTempSrc.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Could not compile fragment shader: " << std::endl;
		std::cout << infoLog << std::endl;
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

entry_point{

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int framebufferWidth, framebufferHeight;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenRender", NULL, NULL);
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);

	GLint err;
	if ((err = glewInit()) != GLEW_OK) {
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << glewGetErrorString(err);
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLuint mainProgram;
	if (!loadShader(mainProgram)) {
		glfwTerminate();
	}

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		updateInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	glDeleteProgram(mainProgram);

	return 0;
}
