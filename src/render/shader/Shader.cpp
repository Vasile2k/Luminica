#include "Shader.hpp"
#include "../../commons/Debug.hpp"
#include "../../commons/GLlibs.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
	char *vertexShaderSource = loadFile(vertexShaderPath);
	char *fragmentShaderSource = loadFile(fragmentShaderPath);

	unsigned int vertexShaderID = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShaderID = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	m_RendererID = CreateProgram(vertexShaderID, fragmentShaderID);
}

Shader::~Shader() {
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const {
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

unsigned int Shader::CompileShader(const char *const shaderSource, unsigned int type) {
	GLCall(unsigned int shaderID = glCreateShader(type));
	GLCall(glShaderSource(shaderID, 1, &shaderSource, nullptr));
	delete[] shaderSource;

	GLCall(glCompileShader(shaderID));

	int compilationResult = 0;
	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationResult));
	if (compilationResult != GL_TRUE) {
		fprintf(stderr, "Failed to compile %s shader.\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");

		int infoLogLength = 0;
		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));
		char log[1024];
		GLCall(glGetShaderInfoLog(shaderID, infoLogLength, nullptr, log));
		fprintf(stderr, "Log: %s\n", log);

		GLCall(glDeleteShader(shaderID));
	}

	return shaderID;
}

char *Shader::loadFile(std::string path) {
	FILE *stream = fopen(path.c_str(), "rb");
	if (stream == nullptr) {
		fprintf(stderr, "Couldn't open file %s\n", path.c_str());
		return nullptr;
	}

	fseek(stream, 0, SEEK_END);
	unsigned long length = ftell(stream);

	char *shaderSource = new char[length + 1];
	fseek(stream, 0, SEEK_SET);
	fread(shaderSource, length, 1, stream);
	fclose(stream);
	shaderSource[length] = '\0';

	return shaderSource;
}

unsigned int Shader::CreateProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID) {
	GLCall(unsigned int shaderID = glCreateProgram());
	GLCall(glAttachShader(shaderID, vertexShaderID));
	GLCall(glAttachShader(shaderID, fragmentShaderID));
	GLCall(glLinkProgram(shaderID));

	int result;
	GLCall(glGetProgramiv(shaderID, GL_LINK_STATUS, &result));
	if (result == GL_FALSE) {
		fprintf(stderr, "Failed to link program\n");

		int infoLogLength;
		GLCall(glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength));

		if (infoLogLength > 0) {
			char *log = static_cast<char *>(malloc(static_cast<unsigned long>((infoLogLength + 1)) * sizeof(char)));
			if (log == nullptr) {
				fprintf(stderr, "Couldn't allocate memory for shader log.");
				exit(EXIT_FAILURE);
			}
			GLCall(glGetProgramInfoLog(shaderID, infoLogLength, nullptr, log));
			fprintf(stderr, "Log: %s\n", log);
			free(log);
		}
		return 0;
	}

	GLCall(glDetachShader(shaderID, vertexShaderID));
	GLCall(glDetachShader(shaderID, fragmentShaderID));
	GLCall(glDeleteShader(vertexShaderID));
	GLCall(glDeleteShader(fragmentShaderID));

	return shaderID;
}

int Shader::GetUniformLocation(const std::string &name) {
	if (m_LocationCache.find(name) != m_LocationCache.end()) {
		return m_LocationCache[name];
	}
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1) {
		std::cout << "Warning: Uniform " << name << " might not exist." << std::endl;
	}
	m_LocationCache[name] = location;
	return location;
}

void Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3) {
	GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniform3f(const std::string & name, float f0, float f1, float f2) {
	GLCall(glUniform3f(GetUniformLocation(name), f0, f1, f2));
}

void Shader::SetUniform2f(const std::string &name, float f0, float f1) {
	GLCall(glUniform2f(GetUniformLocation(name), f0, f1));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4x4& mat) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

void Shader::SetUniform1i(const std::string &name, int val) {
	GLCall(glUniform1i(GetUniformLocation(name), val));
}
