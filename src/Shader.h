#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader {
private:
	GLuint mainProgram;
public:

	Shader(const char* vertFile, const char* fragFile) {
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertFile);
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragFile);

		link(vertexShader, fragmentShader);
	}

	~Shader() {
		glDeleteProgram(this->mainProgram);
	}

	std::string readShader(const char *fn) {
		std::ifstream ifile(fn);
		std::string filetext;
		while (ifile.good()) {
			std::string line;
			std::getline(ifile, line);
			filetext.append(line + "\n");
		
		}
		ifile.close();

		return filetext;
	}

	GLuint loadShader(GLenum typeShader, const char* fn) {

		GLint success;
		char infoLog[512];

		GLuint shader = glCreateShader(typeShader);
		std::string rawShaderSrc = readShader(fn);
		const GLchar* shaderSrc = rawShaderSrc.c_str();
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Could not compile shader: " << fn << std::endl;
			std::cout << infoLog << std::endl;
		}
		return shader;
	}

	void link(GLuint vertexShader, GLuint fragmentShader) {

		GLint success;
		char infoLog[512];

		this->mainProgram = glCreateProgram();
		
		glAttachShader(this->mainProgram, vertexShader);
		glAttachShader(this->mainProgram, fragmentShader);
		glLinkProgram(this->mainProgram);

		glGetProgramiv(this->mainProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->mainProgram, 512, NULL, infoLog);
			std::cout << "Error link program: " << infoLog << std::endl;
		}

		glUseProgram(0);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void use() {
		glUseProgram(this->mainProgram);
	}

	void disable() {
		glUseProgram(0);
	}

	void set1i(GLint value, const GLchar *uniformName) {
		use();

		glUniform1i(glGetUniformLocation(this->mainProgram, uniformName), value);

		disable();
	}

	void setVec1f(GLfloat value, const GLchar *uniformName) {
		use();

		glUniform3fv(glGetUniformLocation(this->mainProgram, uniformName), value);

		disable();
	}

	void setVec3f(glm::fvec2 value, const GLchar *uniformName) {
		use();

		glUniform2fv(glGetUniformLocation(this->mainProgram, uniformName), 1, glm::value_ptr(value));

		disable();
	}

	void setVec3f(glm::fvec3 value, const GLchar *uniformName) {
		use();

		glUniform3fv(glGetUniformLocation(this->mainProgram, uniformName), 1, glm::value_ptr(value));

		disable();
	}

	void setVec4f(glm::fvec4 value, const GLchar *uniformName) {
		use();

		glUniform4fv(glGetUniformLocation(this->mainProgram, uniformName), 1, glm::value_ptr(value));

		disable();
	}

	void setMat4fv(glm::mat3 value, const GLchar *uniformName, GLboolean doTranspose = GL_FALSE) {
		use();

		glUniformMatrix3fv(glGetUniformLocation(this->mainProgram, uniformName), 1, doTranspose, glm::value_ptr(value));

		disable();
	}

	void setMat4fv(glm::mat4 value, const GLchar *uniformName, GLboolean doTranspose = GL_FALSE) {
		use();

		glUniformMatrix4fv(glGetUniformLocation(this->mainProgram, uniformName), 1, doTranspose, glm::value_ptr(value));

		disable();
	}
};