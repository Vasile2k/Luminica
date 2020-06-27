#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#define VERTEX "v"
#define TEXTURE "vt"
#define NORMAL "vn"
#define FACE "f"

#define VERTICES_PER_FACE 3

// pack to byte
#pragma pack(push, 1)
struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	bool operator==(const Vertex &other) const;
};
#pragma pack(pop)

bool Vertex::operator==(const Vertex &other) const {
	return position == other.position && texCoords == other.texCoords/* && normal == other.normal*/;
}

/*
 * T - IndexBuffer data type - defaults to unsigned int
 * U - Vertex data type - defaults to float
 */
template <typename T = unsigned int, typename U = float>
bool Load(const std::string &path, std::vector<Vertex> &vertices, std::vector<T> &indices) {

	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;

	FILE *objFile = fopen(path.c_str(), "rt");
	if (objFile == nullptr) {
		fprintf(stderr, "Couldn't open file %s\n", path.c_str());
		return false;
	}

	char begin[128];

	int currentLine = 0;

	while (fscanf(objFile, "%s", begin) != EOF) {
		if (strcmp(begin, VERTEX) == 0) {
			glm::vec3 position;
			fscanf(objFile, "%f %f %f\n", &position.x, &position.y, &position.z);
			vertexPositions.push_back(position);
		} else if (strcmp(begin, FACE) == 0) {
			glm::uvec3 vertIndex;
			glm::uvec3 texCoordIndex;
			glm::uvec3 normalIndex;

			glm::vec3 tangent;
			glm::vec3 bitangent;

			Vertex v[VERTICES_PER_FACE];

			for (unsigned int i = 0; i < VERTICES_PER_FACE; ++i) {
				fscanf(objFile, "%u/%u/%u ", &vertIndex[i], &texCoordIndex[i], &normalIndex[i]);

				// Create a vertex
				v[i].position = vertexPositions[vertIndex[i] - 1];
				v[i].texCoords = textures[texCoordIndex[i] - 1];
				v[i].normal = normals[normalIndex[i] - 1];
			}

			glm::vec3 edge1 = v[1].position - v[0].position;
			glm::vec3 edge2 = v[2].position - v[0].position;

			glm::vec2 deltaUV1 = v[1].texCoords - v[0].texCoords;
			glm::vec2 deltaUV2 = v[2].texCoords - v[0].texCoords;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			tangent = glm::normalize(tangent);

			bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			bitangent = glm::normalize(bitangent);

			for (unsigned int i = 0; i < VERTICES_PER_FACE; ++i) {

				v[i].tangent = tangent;
				v[i].bitangent = bitangent;

				// Check if it already exists
				auto position = std::find(vertices.begin(), vertices.end(), v[i]);

				// Add it if needed, and add index to it
				if (position == vertices.end()) {
					vertices.push_back(v[i]);
					indices.push_back(vertices.size() - 1);
				} else {
					T pos = static_cast<T>(position - vertices.begin());
					indices.push_back(pos);
				}
			}

		} else if (strcmp(begin, TEXTURE) == 0) {
			glm::vec2 coord;
			fscanf(objFile, "%f %f\n", &coord.x, &coord.y);
			textures.push_back(coord);
		} else if (strcmp(begin, NORMAL) == 0) {
			glm::vec3 coord;
			fscanf(objFile, "%f %f %f\n", &coord.x, &coord.y, &coord.z);
			normals.push_back(coord);
		}
		++currentLine;
	}

	fclose(objFile);

	return true;
}

