#pragma once
#include <string>
#include "../../commons/GLlibs.hpp"
#include "../../commons/Debug.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

class ObjModel {
public:

	float x;
	float y;
	float z;

	ObjModel(const std::string& path);
	~ObjModel();

	void render();

	glm::mat4x4 getModelMatrix();

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	unsigned int indicesSize;
};