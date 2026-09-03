#include "exercise.hpp"

#include <glad/glad.h>

// vertex data
float vertices_2Ts[] = {
	// triangle T1
	-0.5f, 0.0f, 0.0f,	// 0: T1 - Left
	-0.25f, 0.5f, 0.0f,	// 1: T1 - Top
	0.0f, 0.0f, 0.0f,	// 2: T1 - Right
	// triangle T2
	0.0f, 0.0f, 0.0f,	// 3: T2 - Left
	0.25f, 0.5f, 0.0f,	// 4: T2 - Top
	0.5f, 0.0f, 0.0f,	// 5: T2 - Right
};

float vertices[] = {
	// DEFAULT_TRIANGLE
	0.0f, 0.5f, 0.0f,	// 0 - center top
	-0.5f, -0.5f, 0.0f,	// 1 - bottom left
	0.5f, -0.5f, 0.0f,	// 2 - bottom right
	//
	-0.5f, 0.5f, 0.0f,	// 3 - top left
	0.5f, 0.5f, 0.0f,	// 4 - top right
	0.0f, -0.5f, 0.0f,	// 5 - center bottom
	//
	0.0f, 0.0f, 0.0f,	// 6 T2
	0.25f, 0.5f, 0.0f,	// 7 T2
	0.5f, 0.0f, 0.0f,	// 8 T2
};

unsigned int indices[] = {
	3, 1, 2,	// first triangle
	4, 3, 2,	// second triangle
	6, 7, 8,	// T2
};

static GLuint VBO, VAO, EBO;

// Two triangles
static GLuint VBO_2Ts, VAO_2Ts;

namespace exercise {
	Type type = DEFAULT_TRIANGLE;

	const int glsl_aPosAttribute = 0;

	void draw2TsDiffCol(unsigned int shaderProg1, unsigned int shaderProg2) {
		glUseProgram(shaderProg1);
		draw2Ts(3);

		glUseProgram(shaderProg2);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GL_UNSIGNED_INT)));
	}

	void draw2Ts2VAOs2VBOs() {
		draw2Ts(3);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GL_UNSIGNED_INT)));
	}

	void draw2Ts(int count) {
		glBindVertexArray(VAO_2Ts);
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void drawRectangle() {
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void drawDefaultTriangle() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void base2Ts() {
		glGenVertexArrays(1, &VAO_2Ts);
		glGenBuffers(1, &VBO_2Ts);

		glBindVertexArray(VAO_2Ts);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_2Ts);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2Ts), vertices_2Ts, GL_STATIC_DRAW);

		glVertexAttribPointer(glsl_aPosAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(glsl_aPosAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void base() {	
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(glsl_aPosAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(glsl_aPosAttribute);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind (VBO remains attached to VAO)
	}

	void clean() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glDeleteVertexArrays(1, &VAO_2Ts);
		glDeleteBuffers(1, &VBO_2Ts);
	}
}