#include "ObjModel.hpp"
#include <vector>
#include "OBJLoader.hpp"
#include "../../commons/GLlibs.hpp"
#include "../../commons/Debug.hpp"

ObjModel::ObjModel(const std::string & path) : x(0.0F), y(0.0F), z(0.0F) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Load(path, vertices, indices);

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glEnableVertexAttribArray(4));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords)));
	GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
	GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent)));
	GLCall(glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent)));

	GLCall(glGenBuffers(1, &ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
	indicesSize = indices.size();
}

ObjModel::~ObjModel() {

}

void ObjModel::render() {
	GLCall(glBindVertexArray(vao));
	GLCall(glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0));
}

glm::mat4x4 ObjModel::getModelMatrix() {
	return glm::translate(glm::vec3(x, y, z));
}
