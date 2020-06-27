#pragma once

#include "../../commons/GLlibs.hpp"
#include "../../commons/Debug.hpp"


static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
   0.5f, 1.0f, 0.0f,
};

static const unsigned int indices[] = {
	0, 1, 2,
	0, 1, 3
};

class Triangle {
private:

	GLuint vao;
	GLuint vbo;
	GLuint ibo;

public:

	Triangle() {
		GLCall(glGenBuffers(1, &vbo));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));
		
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));
		GLCall(glEnableVertexAttribArray(0));
		
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	~Triangle() {

	}

	void render() {
		GLCall(glBindVertexArray(vao));
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
	}

};
